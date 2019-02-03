/*
  +----------------------------------------------------------------------+
  | mf2: extension for PHP                                               |
  +----------------------------------------------------------------------+
  | Copyright © 2019 Christopher James Willcock                          |
  +----------------------------------------------------------------------+
  | This source file is subject to the MIT License (MIT), that is        |
  | bundled with this package in the file LICENSE.md.                    |
  +----------------------------------------------------------------------+
  | Author: Christopher James Willcock <cjwillcock@ieee.org>             |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#if HAVE_MF2

#include <libxml/parserInternals.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlsave.h>
#include <libxml/xpath.h>

#include "zend_smart_str.h"
#include "ext/libxml/php_libxml.h"
#include "ext/date/php_date.h"
#include "ext/pcre/php_pcre.h"
#include "ext/standard/php_var.h"

#include "mf2.h"
#include "php_mf2.h"
#include "php_mf2parse.h"
#include "mf2microformat.h"
#include "php_mf2microformat.h"

#include "mf2parse.h"

/**
 * Convert a standard zend_object reference to an MF2Parse object reference.
 *
 * A standard zend_object is embedded within each MF2Parse object. Many API
 * functions expect a zend_object parameter, making this function helpful to
 * reference the containing MF2Parse object of the standard zend_object passed
 * by the API.
 *
 * @link https://phpinternals.net/categories/zend_objects#offset
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The reference to a standard zend_object.
 *
 * @return  mf2parse_object *  The containing MF2Parse object.
 */
php_mf2parse_object *mf2parse_fetch_object( zend_object *object )
{
	return ( php_mf2parse_object * ) ( ( char * ) ( object ) - XtOffsetOf( php_mf2parse_object, zo ) );
}

/**
 * Exposes the internal properties of the MF2Parse which correspond to the
 * microformats JSON format.
 *
 * @since 0.1.0
 *
 * @param  zval * object  The subject MF2Parse instance.
 * @param  int * is_temp  Indicates if the return value should be a copy or a
 *                        reference to the memory.
 *
 * @return  HashTable *  The properties of the object.
 */
HashTable *mf2parse_get_properties_ht( zval *object, int is_temp )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	HashTable *ht;
	zval items, rels, rel_urls;

	if ( is_temp ) {
		ALLOC_HASHTABLE( ht );
		zend_hash_init( ht, 0, NULL, ZVAL_PTR_DTOR, 0 );
	} else if ( mf2parse->properties ) {
		zend_hash_clean( mf2parse->properties );
		ht = mf2parse->properties;
	} else {
		php_printf("it actually reached this\n");
	}

	// Add the items
	ZVAL_ARR( &items, mf2parse->items );
	zval_copy_ctor( &items );
	zend_hash_add( ht, MF2_STR( str_items ), &items );

	// Add the rels
	ZVAL_ARR( &rels, mf2parse->rels );
	zval_copy_ctor( &rels );
	zend_hash_add( ht, MF2_STR( str_rels ), &rels );

	// Add the rel_urls
	ZVAL_ARR( &rel_urls, mf2parse->rel_urls );
	zval_copy_ctor( &rel_urls );
	zend_hash_add( ht, MF2_STR( str_rel_urls), &rel_urls );

	return ht;
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_resolve_relative_uri( zval *object, zval *zv_return_value, php_url *relative_url_parts )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	smart_str smart_uri_str = {0};

	static char *scheme_separator       = "://";
	static char *user_or_host_separator = ":";
	static char *user_pass_separator    = "@";
	static char *path_separator         = "/";
	static char *query_separator        = "?";
	static char *fragment_separator     = "#";

	if ( !mf2parse->php_base_url || !mf2parse->php_base_url->scheme ) {
		if ( ! ( mf2parse->options & PHP_MF2_NOWARNING ) ) {
			php_error_docref( NULL, E_WARNING, "Absolute base URL is not set, but is required to resolve a relative HTML <base>" );
		}
		return 0;
	}

	smart_str_appends( &smart_uri_str, !relative_url_parts->scheme ? mf2parse->php_base_url->scheme : relative_url_parts->scheme );
	smart_str_appends( &smart_uri_str, scheme_separator );

	if ( !relative_url_parts->host ) {
		zend_bool has_user_or_pass = 0;

		if ( mf2parse->php_base_url->user ) {
			smart_str_appends( &smart_uri_str, mf2parse->php_base_url->user );
			has_user_or_pass = 1;
		}

		if ( mf2parse->php_base_url->pass ) {
			smart_str_appends( &smart_uri_str, user_or_host_separator );
			smart_str_appends( &smart_uri_str, mf2parse->php_base_url->pass );
			has_user_or_pass = 1;
		}

		if ( has_user_or_pass ) {
			smart_str_appends( &smart_uri_str, user_pass_separator );
		}

		smart_str_appends( &smart_uri_str, mf2parse->php_base_url->host );

		if ( mf2parse->php_base_url->port ) {
			smart_str_appends( &smart_uri_str, user_or_host_separator );
			smart_str_append_long( &smart_uri_str, mf2parse->php_base_url->port );
		}
	}

	if ( relative_url_parts->path ) {
		if ( *relative_url_parts->path != *path_separator ) {
			if ( mf2parse->php_base_url->path ) {
				smart_str_appends( &smart_uri_str, mf2parse->php_base_url->path );
			} else {
				smart_str_appends( &smart_uri_str, path_separator );
			}
			smart_str_appends( &smart_uri_str, relative_url_parts->path );
		} else {
			smart_str_appends( &smart_uri_str, relative_url_parts->path );
		}

		if ( relative_url_parts->query ) {
			smart_str_appends( &smart_uri_str, query_separator );
			smart_str_appends( &smart_uri_str, relative_url_parts->query );
		}

		if ( relative_url_parts->fragment ) {
			smart_str_appends( &smart_uri_str, fragment_separator );
			smart_str_appends( &smart_uri_str, relative_url_parts->fragment );
		}
	} else {
		if ( mf2parse->php_base_url->path ) {
			smart_str_appends( &smart_uri_str, mf2parse->php_base_url->path );
		} else {
			smart_str_appends( &smart_uri_str, path_separator );
		}

		if ( relative_url_parts->query ) {
			smart_str_appends( &smart_uri_str, query_separator );
			smart_str_appends( &smart_uri_str, relative_url_parts->query );
		} else if ( mf2parse->php_base_url->query ) {
			smart_str_appends( &smart_uri_str, query_separator );
			smart_str_appends( &smart_uri_str, mf2parse->php_base_url->query );
		}

		if ( relative_url_parts->fragment ) {
			smart_str_appends( &smart_uri_str, fragment_separator );
			smart_str_appends( &smart_uri_str, relative_url_parts->fragment );
		} else if ( mf2parse->php_base_url->fragment ) {
			smart_str_appends( &smart_uri_str, fragment_separator );
			smart_str_appends( &smart_uri_str,  mf2parse->php_base_url->fragment );
		}
	}

	if ( relative_url_parts->query ) {
		// TODO: finish up relative URL resolution
	}
	smart_str_0( &smart_uri_str );

	zval_ptr_dtor( zv_return_value );
	ZVAL_STRING( zv_return_value, ZSTR_VAL( smart_uri_str.s ) );

	smart_str_free( &smart_uri_str );

	return 1;
}

/**
 * @since 0.1.0
 */
static void mf2parse_resolve_relative_node_attributes( zval *object, xmlNodePtr xml_node )
{
	zval zv_attr, zv_value, zv_temp;

	xmlNodePtr current_node;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {

		switch( current_node->type ) {
			case XML_ELEMENT_NODE:
				ZVAL_NULL( &zv_attr );
				ZVAL_NULL( &zv_value );
				ZVAL_NULL( &zv_temp );

				// We seek src and href attributes.
				MF2_TRY_ZVAL_XMLATTR( zv_value, current_node, MF2_STR( str_href ) );
				if ( IS_NULL == Z_TYPE( zv_value ) ) {
					MF2_TRY_ZVAL_XMLATTR( zv_value, current_node, MF2_STR( str_src ) );
					if ( IS_NULL != Z_TYPE( zv_value ) ) {
						ZVAL_STRING( &zv_attr, ZSTR_VAL( MF2_STR( str_src ) ) );
					}
				} else {
					ZVAL_STRING( &zv_attr, ZSTR_VAL( MF2_STR( str_href ) ) );
				}

				if (
					IS_NULL != Z_TYPE( zv_attr )
				) {
					ZVAL_COPY( &zv_temp, &zv_value );
					MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_value );

					if ( ! xmlStrEqual( ( xmlChar * ) Z_STRVAL( zv_value ), ( xmlChar * ) Z_STRVAL( zv_temp ) ) ) {
						xmlSetProp( current_node, ( xmlChar * ) Z_STRVAL( zv_attr ), ( xmlChar * ) Z_STRVAL( zv_value ) );
					}
				}

				zval_dtor( &zv_attr );
				zval_dtor( &zv_value );
				zval_dtor( &zv_temp );
			break;

			default:
				// Here to fill out the enum and keep the compilier quiet
			break;
		}

		mf2parse_resolve_relative_node_attributes( object, xml_node->children );
	}
}

/**
 * @since 0.1.0
 */
static void mf2parse_resolve_base( zval *object )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );

	xmlXPathContextPtr xpath = xmlXPathNewContext( mf2parse->document );
	if ( xpath == NULL ) {
		if ( ! ( mf2parse->options & PHP_MF2_NOWARNING ) ) {
			php_error_docref( NULL, E_WARNING, "Failed to make an XPath context" );
		}
		return;
	}
	xmlXPathObjectPtr result = xmlXPathEvalExpression( ( xmlChar * ) "//base[@href]", xpath );
	xmlXPathFreeContext( xpath );

	if ( xmlXPathNodeSetIsEmpty( result->nodesetval ) ) {
		xmlXPathFreeObject( result );
		return;
	}

	xmlNodeSetPtr nodeset = result->nodesetval;

	xmlChar *base_href = xmlGetProp( nodeset->nodeTab[0], ( xmlChar * ) ZSTR_VAL( MF2_STR( str_href ) ) );
	xmlXPathFreeObject( result );

	if ( 0 == xmlStrlen( base_href ) ) {
		xmlFree( base_href );
		return;
	}

	php_url *doc_url_parts = php_url_parse( ( char * ) base_href );

	if ( NULL == doc_url_parts ) {
		if ( ! ( mf2parse->options & PHP_MF2_NONOTICE ) ) {
			php_error_docref( NULL, E_NOTICE, "Parsed document includes an invalid <base> URL" );
		}
		xmlFree( base_href );
		return;
	}

	if ( !mf2_is_relative_url( doc_url_parts ) ) {
		// The HTML base is found, and is not relative, so it is the base_url

		// TODO: stop redoing this php_url_parse
		if ( mf2parse->php_base_url ) {
			php_url_free( mf2parse->php_base_url );
		}
		mf2parse->php_base_url = php_url_parse( ( char * ) base_href );

	} else {
		// The HTML base is found, and is relative o_O
		zval zv_href;
		ZVAL_NULL( &zv_href );

		if ( mf2parse_resolve_relative_uri( object, &zv_href, doc_url_parts ) ) {
			if ( mf2parse->php_base_url ) {
				php_url_free( mf2parse->php_base_url );
			}
			mf2parse->php_base_url = php_url_parse( Z_STRVAL( zv_href ) );
		}

		zval_dtor( &zv_href );
	}

	xmlFree( base_href );
	php_url_free( doc_url_parts );
}

/**
 * @since 0.1.0
 */
static void mf2parse_add_rel( zval *object, char *rel, char *href, xmlNodePtr xml_node )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval zv_arr_rels, zv_arr_rel_urls, zv_arr_prop_rels, zv_rel, zv_href, *rels_ptr, *rel_urls_ptr;
	xmlChar *attr;

	ZVAL_STRING( &zv_rel, rel );
	ZVAL_STRING( &zv_href, href );

	mf2_trim_html_space_chars( &zv_href, Z_STRVAL( zv_href ) );
	MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_href );

	// Rels
	if ( ( rels_ptr = zend_hash_find( mf2parse->rels, Z_STR( zv_rel ) ) ) != NULL ) {
		// This rel type has already been recorded, add to that array.
		if ( !mf2_in_array( rels_ptr, &zv_href ) ) {
			add_next_index_string( rels_ptr, Z_STRVAL( zv_href ) );
		}
	} else {
		// This rel is new, create the array
		array_init( &zv_arr_rels );
		add_next_index_string( &zv_arr_rels, Z_STRVAL( zv_href ) );
		zend_hash_add_new( mf2parse->rels, Z_STR( zv_rel ), &zv_arr_rels );
	}

	xmlBufferPtr buffer = xmlBufferCreate();
	xmlNodeBufGetContent( buffer, xml_node );

	// Rel-URLs
	if ( ( rel_urls_ptr = zend_hash_find( mf2parse->rel_urls, Z_STR( zv_href ) ) ) != NULL ) {
		// This URL has already been recorded, add to that array

		// Text Content, if not already set
		if ( zend_hash_find( Z_ARRVAL_P( rel_urls_ptr ), MF2_STR( str_text ) ) == NULL ) {
			if ( xmlStrlen( buffer->content ) > 0 ) {
				add_assoc_string( rel_urls_ptr, ZSTR_VAL( MF2_STR( str_text ) ), ( char * ) buffer->content );
			}
		}

		// Rels
		rels_ptr = zend_hash_find( Z_ARRVAL_P( rel_urls_ptr ), MF2_STR( str_rels ) );
		if ( !mf2_in_array( rels_ptr, &zv_rel ) ) {
			add_next_index_string( rels_ptr, Z_STRVAL( zv_rel ) );
			zend_hash_sort( Z_ARRVAL_P( rels_ptr ), mf2_strcasecmp, 1 );
		}

	} else {
		// This URL is new, create the array
		array_init( &zv_arr_prop_rels );
		add_next_index_string( &zv_arr_prop_rels, Z_STRVAL( zv_rel ) );

		array_init( &zv_arr_rel_urls );

#define X(str) \
		if ( xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_ ## str ) ) ) ) { \
			attr = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_ ## str ) ) ); \
			add_assoc_string( &zv_arr_rel_urls, ZSTR_VAL( MF2_STR( str_ ## str ) ), ( char * ) attr ); \
			xmlFree( attr ); \
		}
		X(hreflang)
		X(media)
		X(title)
		X(type)
#undef X

		// Text Content
		if ( xmlStrlen( buffer->content ) > 0 ) {
			add_assoc_string( &zv_arr_rel_urls, ZSTR_VAL( MF2_STR( str_text ) ), ( char * ) buffer->content );
		}

		// Rels
		add_assoc_zval( &zv_arr_rel_urls, ZSTR_VAL( MF2_STR( str_rels ) ), &zv_arr_prop_rels );

		zend_hash_add_new( mf2parse->rel_urls, Z_STR( zv_href ), &zv_arr_rel_urls );
	}

	// hAtom rel-bookmark and rel-tag parsing
	// hReview rel-self, rel-bookmark and rel-tag parsing
	if (
		NULL != mf2parse->context
		&&
		1 == Z_MF2MFOBJ_P( mf2parse->context )->version
		&&
		(
			mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hfeed ) )
			||
			mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hentry ) )
			||
			mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hnews ) )
			||
			mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hreview ) )
		)
	) {
		zval zv_key;
		ZVAL_NULL( &zv_key );

		if ( zend_string_equals( Z_STR( zv_rel ), MF2_STR( str_tag ) ) ) {
			ZVAL_STRING( &zv_key, ZSTR_VAL( MF2_STR( str_category ) ) );

			zval zv_value;
			ZVAL_STRING( &zv_value, ( char * ) buffer->content );
			mf2microformat_add_property( mf2parse->context, &zv_key, &zv_value );

			zval_dtor( &zv_value );
		} else if (
			(
				zend_string_equals( Z_STR( zv_rel ), MF2_STR( str_bookmark ) )
				&&
				mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hentry ) )
			)
			||
			(
				(
					zend_string_equals( Z_STR( zv_rel ), MF2_STR( str_bookmark ) )
					||
					zend_string_equals( Z_STR( zv_rel ), MF2_STR( str_self ) )
				)
				&&
				mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hreview ) )
			)
		) {
			ZVAL_STRING( &zv_key, ZSTR_VAL( MF2_STR( str_url ) ) );
			mf2microformat_add_property_no_duplicate_values( mf2parse->context, &zv_key, &zv_href );
		} else if (
			zend_string_equals( Z_STR( zv_rel ), MF2_STR( str_principles ) )
			&&
			mf2_string_in_array( &Z_MF2MFOBJ_P( mf2parse->context )->backcompat_types, MF2_STR( str_hnews ) )
		) {
			ZVAL_STRING( &zv_key, ZSTR_VAL( MF2_STR( str_principles ) ) );
			mf2microformat_add_property( mf2parse->context, &zv_key, &zv_href );
		}

		zval_dtor( &zv_key );
	}


	xmlBufferFree( buffer );
	zval_dtor( &zv_rel );
	zval_dtor( &zv_href );
}

/**
 * @since 0.1.0
 */
static void mf2parse_get_rels( zval *object, xmlNodePtr xml_node )
{
	zend_string *zs_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// We seek a, area, and link tags.
	if (
		!zend_string_equals ( zs_name, MF2_STR( str_a ) )
		&&
		!zend_string_equals ( zs_name, MF2_STR( str_link ) )
		&&
		!zend_string_equals ( zs_name, MF2_STR( str_area ) )
	) {
		zend_string_free( zs_name );
		return;
	}

	zend_string_free( zs_name );

	// We seek tags with both rel and href attributes.
	if (
		!xmlHasProp( xml_node, ( xmlChar *) ZSTR_VAL( MF2_STR( str_rel ) ) )
		||
		!xmlHasProp( xml_node, ( xmlChar *) ZSTR_VAL( MF2_STR( str_href ) ) )
	) {
		return;
	}

	xmlChar *rel = NULL, *href = NULL;
	rel = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_rel ) ) );
	href = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_href ) ) );

	char *search_rel = NULL, *last = NULL;
	search_rel = php_strtok_r( (char *) rel, " ", &last );

	while( search_rel ) {
		mf2parse_add_rel( object, search_rel, ( char * ) href, xml_node );
		search_rel = php_strtok_r( NULL, " ", &last );
	}

	xmlFree( rel );
	xmlFree( href );
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_find_v2_roots( zval *object, zval *zv_mf, xmlNodePtr xml_node, zval *zv_classes )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	// Microformats2 Roots
	php_pcre_match_impl( mf2parse->regex_roots, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return 0;
	}

	mf2microformat_new( zv_mf, xml_node );

	php_mf2microformat_object *mf2mf = Z_MF2MFOBJ_P( zv_mf );
	mf2mf->version = 2;

	zval *match_arr, *full_match;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		full_match = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 0 );
		mf2microformat_add_type( zv_mf, full_match );
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );

	return 1;
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_find_backcompat_roots( zval *object, zval *zv_mf, xmlNodePtr xml_node, zval *zv_classes )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	// Classic Microformats (Backcompat) Roots
	php_pcre_match_impl( mf2parse->regex_backcompat_roots, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return 0;
	}

	mf2microformat_new( zv_mf, xml_node );

	php_mf2microformat_object *mf2mf = Z_MF2MFOBJ_P( zv_mf );
	mf2mf->version = 1;

	zval *match_arr, *full_match;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		full_match = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 0 );
		mf2microformat_add_backcompat_type( zv_mf, full_match );
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );

	return 1;
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_roots( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if ( ! xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) ) ) {
		return;
	}

	xmlChar *classes = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) );

	zval zv_classes;
	ZVAL_STRING( &zv_classes, ( char * ) classes );

	// Microformats2 root parsing
	if ( ! mf2parse_find_v2_roots( object, zv_mf, xml_node, &zv_classes ) ) {

		// Backcompat root parsing
		mf2parse_find_backcompat_roots( object, zv_mf, xml_node, &zv_classes );
	}

	zval_dtor( &zv_classes );
	xmlFree( classes );
}

/**
 * @since 0.1.0
 */
static void mf2parse_clean_text_content( zval *object, xmlNodePtr xml_node, zval *zv_return_value )
{
	smart_str clean_content = {0};

	xmlNodePtr current_node;
	zend_string *node_name;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {
		if ( ( current_node->type != XML_ELEMENT_NODE ) && ( current_node->type != XML_TEXT_NODE ) ) {
			continue;
		}

		if ( current_node->type == XML_ELEMENT_NODE ) {
			node_name = zend_string_init( ( char * ) current_node->name, xmlStrlen( current_node->name ), 0 );
			if (
				zend_string_equals( node_name, MF2_STR( str_style ) )
				||
				zend_string_equals( node_name, MF2_STR( str_script ) )
			) {
				zend_string_release( node_name );
				continue;
			}

			if ( zend_string_equals( node_name, MF2_STR( str_img ) ) ) {
				zend_string_release( node_name );

				MF2_TRY_SMART_STR_XMLATTR( clean_content, current_node, MF2_STR( str_alt ) );

				continue;
			}

			zend_string_release( node_name );
		}

		if ( current_node->content ) {
			smart_str_appends( &clean_content, ( char * ) current_node->content );
		}

		if ( current_node->children ) {
			mf2parse_clean_text_content( object, current_node->children, zv_return_value );
			smart_str_appends( &clean_content, Z_STRVAL_P( zv_return_value ) );
			zval_ptr_dtor( zv_return_value );
		}
	}

	smart_str_0( &clean_content );

	if ( clean_content.s && ( ZSTR_LEN( clean_content.s ) > 0 ) ) {
		ZVAL_STR( zv_return_value, clean_content.s );
		zval_copy_ctor( zv_return_value );
		mf2_trim_html_space_chars( zv_return_value, Z_STRVAL_P( zv_return_value ) );
	} else {
		ZVAL_EMPTY_STRING( zv_return_value );
	}

	smart_str_free( &clean_content );
}

/**
 * @since 0.1.0
 */
static void mf2parse_clean_text_content_with_img_src( zval *object, xmlNodePtr xml_node, zval *zv_return_value )
{
	smart_str clean_content = {0};

	xmlNodePtr current_node;
	zend_string *node_name;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {
		if ( ( current_node->type != XML_ELEMENT_NODE ) && ( current_node->type != XML_TEXT_NODE ) ) {
			continue;
		}

		if ( current_node->type == XML_ELEMENT_NODE ) {
			node_name = zend_string_init( ( char * ) current_node->name, xmlStrlen( current_node->name ), 0 );
			if (
				zend_string_equals( node_name, MF2_STR( str_style ) )
				||
				zend_string_equals( node_name, MF2_STR( str_script ) )
			) {
				zend_string_release( node_name );
				continue;
			}

			if ( zend_string_equals( node_name, MF2_STR( str_img ) ) ) {
				zend_string_release( node_name );

				if ( xmlHasProp( current_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_alt ) ) ) ) {
					MF2_SMART_STR_XMLATTR( clean_content, current_node, MF2_STR( str_alt ) );
				} else if ( xmlHasProp( current_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_src ) ) ) ) {
					smart_str_appends( &clean_content, " " );

					zval zv_url;
					MF2_ZVAL_XMLATTR( zv_url, current_node, MF2_STR( str_src ) );

					mf2_trim_html_space_chars( &zv_url, Z_STRVAL( zv_url ) );
					smart_str_appends( &clean_content, Z_STRVAL( zv_url ) );
					smart_str_appends( &clean_content, " " );

					zval_dtor( &zv_url );
				}

				continue;
			}

			zend_string_release( node_name );
		}

		if ( current_node->content ) {
			smart_str_appends( &clean_content, ( char * ) current_node->content );
		}

		if ( current_node->children ) {
			mf2parse_clean_text_content_with_img_src( object, current_node->children, zv_return_value );
			smart_str_appends( &clean_content, Z_STRVAL_P( zv_return_value ) );
			zval_ptr_dtor( zv_return_value );
		}
	}

	smart_str_0( &clean_content );

	if ( clean_content.s && ( ZSTR_LEN( clean_content.s ) > 0 ) ) {
		ZVAL_STR( zv_return_value, clean_content.s );
		zval_copy_ctor( zv_return_value );
	} else {
		ZVAL_EMPTY_STRING( zv_return_value );
	}

	smart_str_free( &clean_content );
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_value_class( zval *object, xmlNodePtr xml_node, zval *zv_return_value )
{
	zend_bool found_vc = 0;
	xmlXPathObjectPtr results;

	xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );

	// TODO: this won't satisfy excluding nested properties with their own values
	results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[contains(concat(' ', @class, ' '), ' value ')]", xpath_context );

	if ( results ) {
		if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
			found_vc = 1;

			smart_str smart_value_str = {0};
			xmlNodePtr current_node;
			zval zv_node_name;

			for ( int idx = 0; idx < results->nodesetval->nodeNr; idx++ ) {

				current_node = results->nodesetval->nodeTab[idx];

				if ( XML_ELEMENT_NODE != current_node->type ) {
					continue;
				}

				ZVAL_STRING( &zv_node_name, ( char * ) current_node->name );

				if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_img ) ) || zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_area ) ) ) {
					// MF2_TRY_SMART_STR_XMLATTR( smart_value_str, current_node, MF2_STR( str_alt ) );
				} else if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_data ) ) ) {
					// MF2_TRY_SMART_STR_XMLATTR_XMLBUFFER( smart_value_str, current_node, MF2_STR( str_value ) );
				} else if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_abbr ) ) ) {
					// MF2_TRY_SMART_STR_XMLATTR_XMLBUFFER( smart_value_str, current_node, MF2_STR( str_title ) );
				} else {
					MF2_SMART_STR_XMLBUFFER( smart_value_str, current_node );
				}

				zval_ptr_dtor( &zv_node_name );
			}

			smart_str_0( &smart_value_str );

			if ( NULL != smart_value_str.s ) {
				ZVAL_STRING( zv_return_value, ZSTR_VAL( smart_value_str.s ) );
			} else {
				ZVAL_EMPTY_STRING( zv_return_value );
			}

			smart_str_free( &smart_value_str );
		}
		xmlXPathFreeObject( results );
	}

	if ( ! found_vc ) {
		// TODO: this won't satisfy excluding nested properties with their own value-titles
		results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[contains(concat(' ', @class, ' '), ' value-title ')]", xpath_context );

		if ( results ) {
			if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
				if ( xmlHasProp( results->nodesetval->nodeTab[0], ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) ) ) {
					found_vc = 1;
					MF2_ZVAL_XMLATTR_P( zv_return_value, results->nodesetval->nodeTab[0], MF2_STR( str_title ) );
				}
			}
			xmlXPathFreeObject( results );
		}
	}

	xmlXPathFreeContext( xpath_context );

	return found_vc;
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_value_class_dt( zval *object, xmlNodePtr xml_node, zval *zv_return_value )
{
	zend_bool found_vc = 0, found_timezone = 0, found_time = 0, found_date = 0;

	xmlXPathObjectPtr results;
	xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );

	// TODO: this won't satisfy excluding nested properties with their own values
	results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[contains(concat(' ', @class, ' '), ' value ')]", xpath_context );

	if ( results ) {
		if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
			found_vc = 1;

			smart_str smart_value_str = {0};
			xmlNodePtr current_node;
			zval zv_node_name, zv_value, zv_date, zv_time, zv_timezone;

			ZVAL_NULL( &zv_date );
			ZVAL_NULL( &zv_time );
			ZVAL_NULL( &zv_timezone );

			for ( int idx = 0; idx < results->nodesetval->nodeNr; idx++ ) {

				current_node = results->nodesetval->nodeTab[idx];
				ZVAL_NULL( &zv_value );

				if ( XML_ELEMENT_NODE != current_node->type ) {
					continue;
				}

				ZVAL_STRING( &zv_node_name, ( char * ) current_node->name );

				if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_img ) ) || zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_area ) ) ) {
					// MF2_TRY_ZVAL_XMLATTR( zv_value, current_node, MF2_STR( str_alt ) );
				} else if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_data ) ) ) {
					// MF2_TRY_ZVAL_XMLATTR_XMLBUFFER( zv_value, current_node, MF2_STR( str_value ) );
				} else if ( zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_abbr ) ) ) {
					// MF2_TRY_ZVAL_XMLATTR_XMLBUFFER( zv_value, current_node, MF2_STR( str_title ) );
				} else if (
					zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_del ) )
					||
					zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_ins ) )
					||
					zend_string_equals( Z_STR( zv_node_name ), MF2_STR( str_time ) )
				) {
					MF2_TRY_ZVAL_XMLATTR_XMLBUFFER( zv_value, current_node, MF2_STR( str_datetime ) );
				} else {
					MF2_ZVAL_XMLBUFFER( zv_value, current_node );
				}

				if ( IS_NULL != Z_TYPE( zv_value ) ) {
					mf2_trim_html_space_chars( &zv_value, Z_STRVAL( zv_value ) );

					if ( ! found_date ) {
						zval matches, matched;
						ZVAL_NULL( &matched );
						ZVAL_NULL( &matches );

						php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_dt_iso8601, Z_STRVAL( zv_value ), Z_STRLEN( zv_value ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

						if ( ( Z_LVAL( matched ) > 0 ) && IS_ARRAY == Z_TYPE( matches ) ) {
							found_date = 1;
							zval *match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 1 );
							ZVAL_COPY( &zv_date, match_part );

							if ( NULL != ( match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 2 ) ) ) {
								found_time = 1;
								ZVAL_COPY( &zv_time, match_part );

								if ( NULL != ( match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 3 ) ) ) {
									found_timezone = 1;
									ZVAL_COPY( &zv_timezone, match_part );
								}
							}
						} // TODO: else YYYY-DDD

						zval_ptr_dtor( &matches );
						zval_ptr_dtor( &matched );
					}

					if ( ! found_time ) {
						zval matches, matched;
						ZVAL_NULL( &matched );
						ZVAL_NULL( &matches );

						php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_dt_time, Z_STRVAL( zv_value ), Z_STRLEN( zv_value ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

						if ( ( Z_LVAL( matched ) > 0 ) && IS_ARRAY == Z_TYPE( matches ) ) {
							found_time = 1;
							zval *match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 1 );
							ZVAL_COPY( &zv_time, match_part );

							if ( NULL != ( match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 2 ) ) ) {
								found_timezone = 1;
								ZVAL_COPY( &zv_timezone, match_part );
							}
						}

						zval_ptr_dtor( &matches );
						zval_ptr_dtor( &matched );
					} else if ( ! found_timezone ) {
						zval matches, matched;
						ZVAL_NULL( &matched );
						ZVAL_NULL( &matches );

						php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_dt_timezone, Z_STRVAL( zv_value ), Z_STRLEN( zv_value ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

						if ( ( Z_LVAL( matched ) > 0 ) && IS_ARRAY == Z_TYPE( matches ) ) {
							found_timezone = 1;
							zval *match_part = zend_hash_index_find( Z_ARRVAL_P( zend_hash_index_find( Z_ARRVAL( matches ), 0 ) ), 1 );
							ZVAL_COPY( &zv_timezone, match_part );
						}

						zval_ptr_dtor( &matches );
						zval_ptr_dtor( &matched );
					}
				}

				zval_dtor( &zv_value );

				zval_ptr_dtor( &zv_node_name );
			}

			if ( IS_NULL != Z_TYPE( zv_date ) ) {
				smart_str_appends( &smart_value_str, Z_STRVAL( zv_date ) );
				zval_ptr_dtor( &Z_MF2MFOBJ_P( Z_MF2PARSEOBJ_P( object )->context )->date_context );
				ZVAL_COPY( &Z_MF2MFOBJ_P( Z_MF2PARSEOBJ_P( object )->context )->date_context, &zv_date );
			} else {
				if ( IS_NULL != Z_TYPE( Z_MF2MFOBJ_P( Z_MF2PARSEOBJ_P( object )->context )->date_context ) ) {
					found_date = 1;
					smart_str_appends( &smart_value_str, Z_STRVAL( Z_MF2MFOBJ_P( Z_MF2PARSEOBJ_P( object )->context )->date_context ) );
				}
			}

			if ( IS_NULL != Z_TYPE( zv_time ) ) {
				if ( found_date ) {
					smart_str_appends( &smart_value_str, " " );
				}
				smart_str_appends( &smart_value_str, Z_STRVAL( zv_time ) );
			}

			if ( ( IS_NULL != Z_TYPE( zv_timezone ) ) && found_time ) {
				smart_str_appends( &smart_value_str, Z_STRVAL( zv_timezone ) );
			}

			smart_str_0( &smart_value_str );

			zval_dtor( &zv_date );
			zval_dtor( &zv_time );
			zval_dtor( &zv_timezone );

			if ( NULL != smart_value_str.s ) {
				ZVAL_STRING( zv_return_value, ZSTR_VAL( smart_value_str.s ) );
			} else {
				ZVAL_EMPTY_STRING( zv_return_value );
			}

			smart_str_free( &smart_value_str );
		}
		xmlXPathFreeObject( results );
	}

	if ( ! found_vc ) {
		// TODO: this won't satisfy excluding nested properties with their own value-titles
		results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[contains(concat(' ', @class, ' '), ' value-title ')]", xpath_context );

		if ( results ) {
			if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
				if ( xmlHasProp( results->nodesetval->nodeTab[0], ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) ) ) {
					found_vc = 1;
					MF2_ZVAL_XMLATTR_P( zv_return_value, results->nodesetval->nodeTab[0], MF2_STR( str_title ) );
				}
			}
			xmlXPathFreeObject( results );
		}
	}

	xmlXPathFreeContext( xpath_context );

	return found_vc;
}

/**
 * @since 0.1.0
 */
static void mf2parse_p_property( zval *object, zval *zv_mf, zval *zv_name, xmlNodePtr xml_node )
{
	zval zv_value;
	ZVAL_NULL( &zv_value );

	Z_MF2MFOBJ_P( zv_mf )->has_p_prop = 1;

	// Priority #1: value-class pattern
	if ( mf2parse_value_class( object, xml_node, &zv_value ) ) {
		// result is in zv_value

	// Priority #2: abbr.p-x[title] or link.p-x[title]
	} else if (
		(
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_abbr ) ) )
			||
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_link ) ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_title ) );

	// Priority #3: data.p-x[value] or input.p-x[value]
	} else if (
		(
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_data ) ) )
			||
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_input ) ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_value ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_value ) );

	// Priority #4: img.p-x[alt] or area.p-x[alt]
	} else if (
		(
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_img ) ) )
			||
			0 == strcasecmp( ( char * ) xml_node->name, ZSTR_VAL( MF2_STR( str_area ) ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_alt ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_alt ) );

	// Catch-all: textContent
	} else {
		mf2parse_clean_text_content_with_img_src( object, xml_node->children, &zv_value );

		// Include itemref textContent, only for backcompat roots
		if (
			1 == Z_MF2MFOBJ_P( zv_mf )->version
			&&
			xmlHasProp( xml_node, ( xmlChar *) ZSTR_VAL( MF2_STR( str_itemref ) ) )
		) {
			smart_str ss_with_microdata = {0};
			smart_str_appends( &ss_with_microdata, Z_STRVAL( zv_value ) );

			zval zv_itemref;
			ZVAL_NULL( &zv_itemref );
			MF2_TRY_ZVAL_XMLATTR( zv_itemref, xml_node, MF2_STR( str_itemref ) );

			if ( IS_NULL != Z_TYPE( zv_itemref ) ) {
				char *search_class = NULL, *last = NULL;
				zval zv_search_class;
				ZVAL_NULL( &zv_search_class );
				search_class = php_strtok_r( Z_STRVAL( zv_itemref ), " ", &last );

				zval zv_classes;
				ZVAL_NULL( &zv_classes );
				MF2_TRY_ZVAL_XMLATTR( zv_classes, xml_node, MF2_STR( str_class ) );

				while( search_class ) {
					ZVAL_STRING( &zv_search_class, search_class );

					smart_str ss_xpath = {0};
					smart_str_appendl( &ss_xpath, "//*[@id='", sizeof( "//*[@id='" ) - 1 );

					smart_str_appendl( &ss_xpath, Z_STRVAL( zv_search_class ), Z_STRLEN( zv_search_class ) );

					smart_str_appendl( &ss_xpath, "']", sizeof( "']" ) - 1 );
					smart_str_0( &ss_xpath );

					xmlXPathObjectPtr xpath_results;
					xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );

					xpath_results = xmlXPathEval( ( xmlChar * ) ZSTR_VAL( ss_xpath.s ), xpath_context );
					smart_str_free( &ss_xpath );

					if ( xpath_results ) {
						if ( ! xmlXPathNodeSetIsEmpty( xpath_results->nodesetval ) ) {
							MF2_SMART_STR_XMLBUFFER( ss_with_microdata, xpath_results->nodesetval->nodeTab[0] );
						}

						xmlXPathFreeObject( xpath_results );
					}

					xmlXPathFreeContext( xpath_context );

					smart_str_0( &ss_with_microdata );
					mf2_trim_html_space_chars( &zv_value, ZSTR_VAL( ss_with_microdata.s ) );
					smart_str_free( &ss_with_microdata );

					search_class = php_strtok_r( NULL, " ", &last );
					zval_dtor( &zv_search_class );
				}

				zval_dtor( &zv_classes );
			}

			zval_dtor( &zv_itemref );
		}

		mf2_trim_html_space_chars( &zv_value, Z_STRVAL( zv_value ) );
	}

	if ( IS_NULL != Z_TYPE( zv_value ) ) {
		mf2microformat_add_property( zv_mf, zv_name, &zv_value );
	}

	zval_dtor( &zv_value );
}

/**
 * @since 0.1.0
 */
static void mf2parse_u_property( zval *object, zval *zv_mf, zval *zv_name, xmlNodePtr xml_node )
{
	zval zv_value;
	ZVAL_NULL( &zv_value );

	Z_MF2MFOBJ_P( zv_mf )->has_u_prop = 1;

	zend_string *node_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// Priority #1: a.u-x[href] or area.u-x[href] or link.u-x[href]
	if (
		(
			zend_string_equals( node_name, MF2_STR( str_a ) )
			||
			zend_string_equals( node_name, MF2_STR( str_link ) )
			||
			zend_string_equals( node_name, MF2_STR( str_area ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_href ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_href ) );
		MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_value );

	// Priority #2: img.u-x[src]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_img ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_src ) ) )
	) {
		zval zv_src;
		MF2_ZVAL_XMLATTR( zv_src, xml_node, MF2_STR( str_src ) );
		MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_src );

		if ( xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_alt ) ) ) ) {
			zval zv_alt;
			MF2_ZVAL_XMLATTR( zv_alt, xml_node, MF2_STR( str_alt ) );

			array_init( &zv_value );
			add_assoc_zval( &zv_value, ZSTR_VAL( MF2_STR( str_value ) ), &zv_src );
			zval_copy_ctor( &zv_src );
			add_assoc_zval( &zv_value, ZSTR_VAL( MF2_STR( str_alt ) ), &zv_alt );
			zval_copy_ctor( &zv_alt );

			zval_dtor( &zv_alt );
		} else {
			ZVAL_ZVAL( &zv_value, &zv_src, 1, 0 );
		}

		zval_dtor( &zv_src );

	// Priority #3: audio.u-x[src] or video.u-x[src] or source.u-x[src] or iframe.u-x[src]
	} else if (
		(
			zend_string_equals( node_name, MF2_STR( str_audio ) )
			||
			zend_string_equals( node_name, MF2_STR( str_video ) )
			||
			zend_string_equals( node_name, MF2_STR( str_src ) )
			||
			zend_string_equals( node_name, MF2_STR( str_iframe ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_src ) ) )
	) {

		// TODO: Test and Parse

	// Priority #4: video.u-x[poster]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_video ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_poster ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_poster ) );
		MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_value );

	// Priority #5: object.u-x[data]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_object ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_data ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_data ) );

	// Priority #6: value-class pattern
	} else if ( mf2parse_value_class( object, xml_node, &zv_value ) ) {
		// result is in zv_value

	// Priority #7: abbr.u-x[title]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_abbr ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_title ) );

	// Priority #8: data.u-x[value] or input.u-x[value]
	} else if (
		(
			zend_string_equals( node_name, MF2_STR( str_data ) )
			||
			zend_string_equals( node_name, MF2_STR( str_input ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_value ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_value ) );

	// Catch-all: textContent
	} else {

		xmlBufferPtr buffer = xmlBufferCreate();
		xmlNodeBufGetContent( buffer, xml_node );

		// TODO remove script & style, replace img with alt
		ZVAL_STRING( &zv_value, ( char * ) buffer->content );
		xmlBufferFree( buffer );

		mf2_trim_html_space_chars( &zv_value, Z_STRVAL( zv_value ) );
	}

	if ( IS_NULL != Z_TYPE( zv_value ) ) {
		mf2microformat_add_property( zv_mf, zv_name, &zv_value );
	}

	zend_string_free( node_name );
	zval_ptr_dtor( &zv_value );
}

/**
 * @since 0.1.0
 */
static void mf2parse_dt_property( zval *object, zval *zv_mf, zval *zv_name, xmlNodePtr xml_node )
{

	zval zv_value;
	ZVAL_NULL( &zv_value );

	Z_MF2MFOBJ_P( zv_mf )->has_dt_prop = 1;

	zend_string *node_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// Priority #1: value-class pattern
	if ( mf2parse_value_class_dt( object, xml_node, &zv_value ) ) {
		// result is in zv_value

	// Priority #2: time.dt-x[datetime] or ins.dt-x[datetime] or del.dt-x[datetime]
	} else if (
		(
			zend_string_equals( node_name, MF2_STR( str_time ) )
			||
			zend_string_equals( node_name, MF2_STR( str_ins ) )
			||
			zend_string_equals( node_name, MF2_STR( str_del ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_datetime ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_datetime ) );

	// Priority #3: abbr.dt-x[title]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_abbr ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_title ) );

	// Priority #4: data.dt-x[value] or input.dt-x[value]
	} else if (
		(
			zend_string_equals( node_name, MF2_STR( str_data ) )
			||
			zend_string_equals( node_name, MF2_STR( str_input ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_value ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_value, xml_node, MF2_STR( str_value ) );

	// Catch-all: textContext
	} else {
		mf2parse_clean_text_content_with_img_src( object, xml_node->children, &zv_value );
		mf2_trim_html_space_chars( &zv_value, Z_STRVAL( zv_value ) );
	}

	zend_string_free( node_name );

	if ( IS_NULL == Z_TYPE( zv_value ) ) {
		return;
	}

	zval zv_datetime;
	php_date_instantiate( php_date_get_date_ce(), &zv_datetime );

	if ( ( Z_STRLEN( zv_value ) > 0 ) && php_date_initialize( Z_PHPDATE_P( &zv_datetime ), Z_STRVAL( zv_value ), Z_STRLEN( zv_value ), NULL, NULL, 0 ) ) {
		add_property_zval( &zv_datetime, ZSTR_VAL( MF2_STR( str_value ) ), &zv_value );
		mf2microformat_add_property( zv_mf, zv_name, &zv_datetime );
	} else {
		mf2microformat_add_property( zv_mf, zv_name, &zv_value );
	}

	zval_dtor( &zv_value );
	zval_ptr_dtor( &zv_datetime );
}

/**
 * @since 0.1.0
 */
static void mf2parse_e_property( zval *object, zval *zv_mf, zval *zv_name, xmlNodePtr xml_node )
{
	Z_MF2MFOBJ_P( zv_mf )->has_e_prop = 1;

	zval zv_html, zv_set, zv_value;

	array_init( &zv_set );
	ZVAL_NULL( &zv_html );
	ZVAL_NULL( &zv_value );

	xmlBufferPtr buffer = xmlBufferCreate();
	xmlSaveCtxtPtr ctxt = xmlSaveToBuffer( buffer, NULL, 0 );

	// TODO: as written, resolving relative attributes changes the document, is this a problem?

	xmlNodePtr current_node = xml_node->children;
	mf2parse_resolve_relative_node_attributes( object, current_node );

	while ( current_node ) {
		xmlSaveTree( ctxt, current_node );
		current_node = current_node->next;
	}

	xmlSaveClose( ctxt );
	ZVAL_STRING( &zv_html, ( char * ) buffer->content );
	xmlBufferFree( buffer );

	mf2_trim_html_space_chars( &zv_html, Z_STRVAL( zv_html ) );

	add_assoc_zval( &zv_set, ZSTR_VAL( MF2_STR( str_html ) ), &zv_html );
	zval_copy_ctor( &zv_html );

	mf2parse_clean_text_content_with_img_src( object, xml_node->children, &zv_value );
	mf2_trim_html_space_chars( &zv_value, Z_STRVAL( zv_value ) );
	add_assoc_zval( &zv_set, ZSTR_VAL( MF2_STR( str_value ) ), &zv_value );
	Z_ADDREF( zv_value );

	mf2microformat_add_property( zv_mf, zv_name, &zv_set );

	zval_ptr_dtor( &zv_set );
	zval_dtor( &zv_html );
	zval_dtor( &zv_value );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_v2_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	// Microformats2 Properties
	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_prefix, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_prefix = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );
		zv_name   = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 2 );

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, zv_prefix );
			zval_copy_ctor( zv_prefix );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		// TODO: faster way?

		if ( zend_string_equals( MF2_STR( str_p ), Z_STR_P( zv_prefix ) ) ) {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );
		} else if ( zend_string_equals( MF2_STR( str_u ), Z_STR_P( zv_prefix ) ) ) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );
		} else if ( zend_string_equals( MF2_STR( str_dt ), Z_STR_P( zv_prefix ) ) ) {
			mf2parse_dt_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );
		} else if ( zend_string_equals( MF2_STR( str_e ), Z_STR_P( zv_prefix ) ) ) {
			mf2parse_e_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );
		}

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_adr_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_adr_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_string( &zv_parents, "p" );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );

		add_next_index_string( zv_parsed_properties, Z_STRVAL_P( zv_name ) );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_geo_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_geo_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_string( &zv_parents, "p" );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );

		add_next_index_string( zv_parsed_properties, Z_STRVAL_P( zv_name ) );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hcalendar_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hcalendar_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) ) ) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtstart ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtend ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_duration ) )
		) {
			ZVAL_STRING( &zv_prefix, "dt" );

			if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtstart ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_start ) ) );
			} else if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtend ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_end ) ) );
			}

		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_summary ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) ) ) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtstart ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtend ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_duration ) )
		) {
			mf2parse_dt_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hcard_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hcard_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_email ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_logo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_uid ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_key ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_sound ) )
		) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_bday ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_rev ) )
		) {
			ZVAL_STRING( &zv_prefix, "dt" );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_fn ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			} else if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_title ) ) ) {
				ZVAL_STRING( &zv_compat_name, "job-title" );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_email ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_logo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_uid ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_key ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_sound ) )
		) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_bday ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_rev ) )
		) {
			mf2parse_dt_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hfeed_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hfeed_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hentry_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hentry_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), "entry-content" ) ) {
			ZVAL_STRING( &zv_prefix, "e" );
			ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_content ) ) );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_published ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_updated ) )
		) {
			ZVAL_STRING( &zv_prefix, "dt" );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), "entry-title" ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			}

			if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), "entry-summary" ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_summary ) ) );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), "entry-content" ) ) {
			mf2parse_e_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_published ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_updated ) )
		) {
			mf2parse_dt_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hnews_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hnews_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_string( &zv_parents, "p" );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );

		add_next_index_string( zv_parsed_properties, Z_STRVAL_P( zv_name ) );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hproduct_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hproduct_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), ZSTR_VAL( MF2_STR( str_fn ) ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hreview_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hreview_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtreviewed ) )
		) {
			ZVAL_STRING( &zv_prefix, "dt" );

			if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtreviewed ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_reviewed ) ) );
			}
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_description ) )
		) {
			ZVAL_STRING( &zv_prefix, "e" );
			ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_content ) ) );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_summary ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			} else if ( zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_reviewer ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_author ) ) );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_dtreviewed ) )
		) {
			mf2parse_dt_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_description ) )
		) {
			mf2parse_e_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hitem_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hitem_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval zv_prefix, zv_compat_name, *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		ZVAL_NULL( &zv_prefix );
		ZVAL_NULL( &zv_compat_name );

		// TODO: deduplication

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			ZVAL_STRING( &zv_prefix, "u" );
		} else {
			ZVAL_STRING( &zv_prefix, "p" );

			if ( 0 == strcasecmp( Z_STRVAL_P( zv_name ), ZSTR_VAL( MF2_STR( str_fn ) ) ) ) {
				ZVAL_STRING( &zv_compat_name, ZSTR_VAL( MF2_STR( str_name ) ) );
			}
		}

		if ( IS_NULL == Z_TYPE( zv_compat_name ) ) {
			ZVAL_COPY( &zv_compat_name, zv_name );
		}

		if ( mf2_in_array( zv_parsed_properties, &zv_compat_name ) ) {
			zval_ptr_dtor( &zv_compat_name );
			zval_ptr_dtor( &zv_prefix );
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_zval( &zv_parents, &zv_prefix );
			zval_copy_ctor( &zv_prefix );

			add_next_index_zval( &zv_parents, &zv_compat_name );
			zval_copy_ctor( &zv_compat_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		if (
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_photo ) )
			||
			zend_string_equals( Z_STR_P( zv_name ), MF2_STR( str_url ) )
		) {
			mf2parse_u_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		} else {
			mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, &zv_compat_name, xml_node );
		}

		add_next_index_string( zv_parsed_properties, Z_STRVAL( zv_compat_name ) );

		zval_ptr_dtor( &zv_compat_name );
		zval_ptr_dtor( &zv_prefix );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hreview_aggregate_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hreview_aggregate_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_string( &zv_parents, "p" );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );

		add_next_index_string( zv_parsed_properties, Z_STRVAL_P( zv_name ) );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_hresume_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_parsed_properties )
{
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	php_pcre_match_impl( Z_MF2PARSEOBJ_P( object )->regex_backcompat_hresume_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	zval *zv_name, *match_arr;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_name = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );

		if ( mf2_in_array( zv_parsed_properties, zv_name ) ) {
			continue;
		}

		if ( node_has_root ) {
			zval zv_parents;
			array_init( &zv_parents );

			add_next_index_string( &zv_parents, "p" );

			add_next_index_zval( &zv_parents, zv_name );
			zval_copy_ctor( zv_name );

			add_next_index_zval( &( Z_MF2MFOBJ_P( zv_mf_embedded )->contexts ), &zv_parents );
		}

		mf2parse_p_property( object, Z_MF2PARSEOBJ_P( object )->context, zv_name, xml_node );

		add_next_index_string( zv_parsed_properties, Z_STRVAL_P( zv_name ) );

	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_backcompat_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zval *zv_classes, zend_bool node_has_root, zval *zv_type, zval *zv_parsed_properties )
{
	// TODO: combine regexes?

	// TODO: faster?

	/** hCard.
	 * @link http://microformats.org/wiki/hCard */
	if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_vcard ) ) ) {
		mf2parse_find_backcompat_hcard_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hAtom.
	 * @link http://microformats.org/wiki/hAtom */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hfeed ) ) ) {
		mf2parse_find_backcompat_hfeed_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hentry ) ) ) {
		mf2parse_find_backcompat_hentry_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hNews.
	 * @link http://microformats.org/wiki/hNews */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hnews ) ) ) {
		mf2parse_find_backcompat_hnews_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hCalendar.
	 * @link http://microformats.org/wiki/hCalendar */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_vevent ) ) ) {
		mf2parse_find_backcompat_hcalendar_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hProduct.
	 * @link http://microformats.org/wiki/hProduct */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hproduct ) ) ) {
		mf2parse_find_backcompat_hproduct_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hReview.
	 * @link http://microformats.org/wiki/hReview */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hreview ) ) ) {
		mf2parse_find_backcompat_hreview_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_item ) ) ) {
		mf2parse_find_backcompat_hitem_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hreview-aggregate.
	 * @link http://microformats.org/wiki/hreview-aggregate */
	} else if ( 0 == strcasecmp( Z_STRVAL_P( zv_type ), "hreview-aggregate" ) ) {
		mf2parse_find_backcompat_hreview_aggregate_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hResume.
	 * @link http://microformats.org/wiki/hResume */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hresume ) ) ) {
		mf2parse_find_backcompat_hresume_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** hRecipe.
	 * @link http://microformats.org/wiki/hRecipe */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hrecipe ) ) ) {
		// mf2parse_find_backcompat_hrecipe_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** adr.
	 * @link http://microformats.org/wiki/adr */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_adr ) ) ) {
		mf2parse_find_backcompat_adr_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );

	/** geo.
	 * @link http://microformats.org/wiki/geo */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_geo ) ) ) {
		mf2parse_find_backcompat_geo_properties( object, zv_mf_embedded, xml_node, zv_classes, node_has_root, zv_parsed_properties );
	}
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_properties( zval *object, zval *zv_mf_embedded, xmlNodePtr xml_node, zend_bool node_has_root )
{
	if ( ! xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) ) ) {
		return;
	}

	zval zv_classes;
	MF2_ZVAL_XMLATTR( zv_classes, xml_node, MF2_STR( str_class ) );

	if ( 2 == Z_MF2MFOBJ_P( Z_MF2PARSEOBJ_P( object )->context )->version ) {
		// Microformats2 property parsing
		mf2parse_find_v2_properties( object, zv_mf_embedded, xml_node, &zv_classes, node_has_root );
	} else {
		// Classic Microformats (Backcompat) property parsing
		zval zv_parsed_properties;
		array_init( &zv_parsed_properties );

		zval *zv_type;
		ZEND_HASH_FOREACH_VAL( Z_ARRVAL_P( mf2microformat_get_backcompat_types( Z_MF2PARSEOBJ_P( object )->context ) ), zv_type ) {
			mf2parse_find_backcompat_properties( object, zv_mf_embedded, xml_node, &zv_classes, node_has_root, zv_type, &zv_parsed_properties );
		} ZEND_HASH_FOREACH_END();

		zval_ptr_dtor( &zv_parsed_properties );
	}

	zval_dtor( &zv_classes );
}

/**
 * @since 0.1.0
 */
static void mf2parse_imply_name( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if ( Z_MF2MFOBJ_P( zv_mf )->has_p_prop || Z_MF2MFOBJ_P( zv_mf )->has_e_prop ) {
		return;
	}

	if ( mf2microformat_has_property( zv_mf, MF2_STR( str_name ) ) ) {
		return;
	}

	zval zv_name;
	ZVAL_NULL( &zv_name );

	zend_string *node_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// Priority #1: img.h-x or area.h-x
	if (
		zend_string_equals( node_name, MF2_STR( str_img ) )
		||
		zend_string_equals( node_name, MF2_STR( str_area ) )
	) {
		MF2_ZVAL_XMLATTR( zv_name, xml_node, MF2_STR( str_alt ) );

	// Priority #2: abbr.h-x[title]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_abbr ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_title ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_name, xml_node, MF2_STR( str_title ) );

	} else {
		xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );
		xmlXPathObjectPtr results;

		zend_bool done = 0;

		// Priority #3: .h-x>img[alt]:only-child:not([alt=""]):not[.h-*]
		results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "img[@alt[not(.=\"\")]][count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
		if ( results ) {
			if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
				done = 1;
				MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
			}
			xmlXPathFreeObject( results );
		}

		// Priority #4: .h-x>area[alt]:only-child:not([alt=""]):not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "area[@alt[not(.=\"\")]][count(../area) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #5: .h-x>abbr[title]:only-child:not([title=""]):not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "abbr[@title[not(.=\"\")]][count(../abbr) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_title ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #6: .h-x>:only-child:not[.h-*]>img[alt]:only-child:not([alt=""]):not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/img[@alt[not(.=\"\")]][count(../img) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #7: .h-x>:only-child:not[.h-*]>area[alt]:only-child:not([alt=""]):not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/area[@alt[not(.=\"\")]][count(../area) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #8: .h-x>:only-child:not[.h-*]>abbr[title]:only-child:not([title=""]):not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/abbr[@title[not(.=\"\")]][count(../abbr) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_name, results->nodesetval->nodeTab[0], MF2_STR( str_title ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		xmlXPathFreeContext( xpath_context );

		// Catch-all: textContent
		if ( ! done ) {
			mf2parse_clean_text_content( object, xml_node->children, &zv_name );
		}
	}

	zend_string_free( node_name );

	if ( IS_NULL == Z_TYPE( zv_name ) ) {
		return;
	}

	zval zv_key_name;
	ZVAL_STR( &zv_key_name, MF2_STR( str_name ) );
	mf2microformat_add_property( zv_mf, &zv_key_name, &zv_name );

	zval_ptr_dtor( &zv_name );
}

/**
 * @since 0.1.0
 */
static void mf2parse_imply_photo( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if ( Z_MF2MFOBJ_P( zv_mf )->has_u_prop ) {
		return;
	}

	if ( mf2microformat_has_property( zv_mf, MF2_STR( str_photo ) ) ) {
		return;
	}

	zval zv_photo, zv_alt;
	ZVAL_NULL( &zv_photo );
	ZVAL_NULL( &zv_alt );

	zend_string *node_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// Priority #1: img.h-x[src]
	if (
		zend_string_equals( node_name, MF2_STR( str_img ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_src ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_photo, xml_node, MF2_STR( str_src ) );
		MF2_TRY_ZVAL_XMLATTR( zv_alt, xml_node, MF2_STR( str_alt ) );

	// Priority #2: object.h-x[data]
	} else if (
		zend_string_equals( node_name, MF2_STR( str_object ) )
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_data ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_photo, xml_node, MF2_STR( str_data ) );

	} else {
		xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );
		xmlXPathObjectPtr results;

		zend_bool done = 0;

		// Priority #3: .h-x>img[src]:only-of-type:not[.h-*]
		results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "img[@src][count(../img) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
		if ( results ) {
			if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
				done = 1;
				MF2_ZVAL_XMLATTR( zv_photo, results->nodesetval->nodeTab[0], MF2_STR( str_src ) );
				MF2_TRY_ZVAL_XMLATTR( zv_alt, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
			}
			xmlXPathFreeObject( results );
		}

		// Priority #4: .h-x>object[data]:only-of-type:not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "object[@data][count(../object) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );

			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_photo, results->nodesetval->nodeTab[0], MF2_STR( str_data ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #5: .h-x>:only-child:not[.h-*]>img[src]:only-of-type:not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/img[@src][count(../img) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );

			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_photo, results->nodesetval->nodeTab[0], MF2_STR( str_src ) );
					MF2_TRY_ZVAL_XMLATTR( zv_alt, results->nodesetval->nodeTab[0], MF2_STR( str_alt ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #6: .h-x>:only-child:not[.h-*]>object[data]:only-of-type:not[.h-*]
		if ( !done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/object[@data][count(../object) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );

			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					MF2_ZVAL_XMLATTR( zv_photo, results->nodesetval->nodeTab[0], MF2_STR( str_data ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		xmlXPathFreeContext( xpath_context );
	}

	zend_string_free( node_name );

	if ( IS_NULL == Z_TYPE( zv_photo ) ) {
		return;
	}

	MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_photo );

	if ( IS_NULL != Z_TYPE( zv_alt ) ) {

		zval zv_img_array;
		array_init( &zv_img_array );
		add_assoc_zval( &zv_img_array, ZSTR_VAL( MF2_STR( str_value ) ), &zv_photo );
		zval_copy_ctor( &zv_photo );
		add_assoc_zval( &zv_img_array, ZSTR_VAL( MF2_STR( str_alt ) ), &zv_alt );
		zval_copy_ctor( &zv_alt );

		zval_dtor( &zv_photo );
		ZVAL_ZVAL( &zv_photo, &zv_img_array, 0, 0);

		zval_dtor( &zv_alt );
	}

	zval zv_name;
	ZVAL_STR( &zv_name, MF2_STR( str_photo ) );
	mf2microformat_add_property( zv_mf, &zv_name, &zv_photo );

	zval_ptr_dtor( &zv_photo );
}

/**
 * @since 0.1.0
 */
static void mf2parse_imply_url( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if ( Z_MF2MFOBJ_P( zv_mf )->has_u_prop ) {
		return;
	}

	if ( mf2microformat_has_property( zv_mf, MF2_STR( str_url ) ) ) {
		return;
	}

	zend_string *node_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	zval zv_href;
	ZVAL_NULL( &zv_href );

	// Priority #1: a.h-x[href] or area.h-x[href]
	if (
		(
			zend_string_equals( node_name, MF2_STR( str_a ) )
			||
			zend_string_equals( node_name, MF2_STR( str_area ) )
		)
		&&
		xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_href ) ) )
	) {
		MF2_ZVAL_XMLATTR( zv_href, xml_node, MF2_STR( str_href ) );

	} else {
		xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );
		xmlXPathObjectPtr results;

		zend_bool done = 0;

		// Priority #2: .h-x>a[href]:only-of-type:not[.h-*]
		results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "a[@href][count(../a) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
		if ( results ) {
			if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
				done = 1;
				MF2_ZVAL_XMLATTR( zv_href, results->nodesetval->nodeTab[0], MF2_STR( str_href ) );
			}
			xmlXPathFreeObject( results );
		}

		// Priority #3: .h-x>area[href]:only-of-type:not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "area[@href][count(../area) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_href, results->nodesetval->nodeTab[0], MF2_STR( str_href ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #4: .h-x>:only-child:not[.h-*]>a[href]:only-of-type:not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*//*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/a[@href][count(../a) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					// MF2_ZVAL_XMLATTR( zv_href, results->nodesetval->nodeTab[0], MF2_STR( str_href ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		// Priority #5: .h-x>:only-child:not[.h-*]>area[href]:only-of-type:not[.h-*]
		if ( ! done ) {
			results = xmlXPathNodeEval( xml_node, ( xmlChar * ) "*[count(../*) = 1][not(contains(concat(\" \", @class), \" h-\"))]/area[@href][count(../area) = 1][not(contains(concat(\" \", @class), \" h-\"))]", xpath_context );
			if ( results ) {
				if ( ! xmlXPathNodeSetIsEmpty( results->nodesetval ) ) {
					done = 1;
					MF2_ZVAL_XMLATTR( zv_href, results->nodesetval->nodeTab[0], MF2_STR( str_href ) );
				}
				xmlXPathFreeObject( results );
			}
		}

		xmlXPathFreeContext( xpath_context );
	}

	zend_string_free( node_name );

	if ( IS_NULL == Z_TYPE( zv_href ) ) {
		return;
	}

	mf2_trim_html_space_chars( &zv_href, Z_STRVAL( zv_href ) );
	MF2PARSE_RESOLVE_RELATIVE_URI( object, zv_href );

	zval zv_name;
	ZVAL_STR( &zv_name, MF2_STR( str_url ) );

	mf2microformat_add_property( zv_mf, &zv_name, &zv_href );

	zval_dtor( &zv_href );
}

/**
 * @since 0.1.0
 */
static void mf2parse_imply_properties( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	// Only on v2 roots
	if ( 2 != Z_MF2MFOBJ_P( zv_mf )->version ) {
		return;
	}

	// Only if there are no nested microformats
	if ( mf2microformat_has_children( zv_mf ) ) {
		return;
	}

	// TODO: parsing spec, property-embedded microformats disqualify node from implied property parsing (?)

	mf2parse_imply_name( object, zv_mf, xml_node );
	mf2parse_imply_photo( object, zv_mf, xml_node );
	mf2parse_imply_url( object, zv_mf, xml_node );
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_has_include_pattern( zval *object, xmlNodePtr xml_node ) {
	zend_bool result = 0;

	zval zv_classes;
	ZVAL_NULL( &zv_classes );
	MF2_TRY_ZVAL_XMLATTR( zv_classes, xml_node, MF2_STR( str_class ) );

	if( IS_NULL != Z_TYPE( zv_classes ) ) {
		char *search_class = NULL, *last = NULL;
		search_class = php_strtok_r( Z_STRVAL( zv_classes ), " ", &last );

		while( search_class ) {
			if ( 0 == strcasecmp( search_class, ZSTR_VAL( MF2_STR( str_include ) ) ) ) {
				result = 1;
				break;
			}
			search_class = php_strtok_r( NULL, " ", &last );
		}
	}

	zval_dtor( &zv_classes );

	return result;
}

/**
 * @since 0.1.0
 */
static zend_bool mf2parse_has_table_headers( zval *object, xmlNodePtr xml_node ) {
	return xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_headers ) ) ) ? 1 : 0;
}

/**
 * @since 0.1.0
 */
static void mf2parse_referenced_node_id( zval *object, zval *zv_id, zend_bool skip_first_char )
{
	smart_str ss_xpath = {0};
	smart_str_appendl( &ss_xpath, "//*[@id='", sizeof( "//*[@id='" ) - 1 );

	if ( skip_first_char ) {
		// Using [1] as start of zv_id cstr, skips # char
		smart_str_appendl( &ss_xpath, &( Z_STRVAL_P( zv_id )[1] ), Z_STRLEN_P( zv_id ) - 1 );
	} else {
		smart_str_appendl( &ss_xpath, Z_STRVAL_P( zv_id ), Z_STRLEN_P( zv_id ) );
	}

	smart_str_appendl( &ss_xpath, "']", sizeof( "']" ) - 1 );
	smart_str_0( &ss_xpath );

	xmlXPathObjectPtr xpath_results;
	xmlXPathContextPtr xpath_context = xmlXPathNewContext( Z_MF2PARSEOBJ_P( object )->document );

	xpath_results = xmlXPathEval( ( xmlChar * ) ZSTR_VAL( ss_xpath.s ), xpath_context );
	smart_str_free( &ss_xpath );

	if ( xpath_results ) {
		if ( ! xmlXPathNodeSetIsEmpty( xpath_results->nodesetval ) ) {
			mf2parse_xml_node( object, xpath_results->nodesetval->nodeTab[0], 1 );
		}

		xmlXPathFreeObject( xpath_results );
	}

	xmlXPathFreeContext( xpath_context );
}

/**
 * @since 0.1.0
 */
static void mf2parse_include_pattern( zval *object, xmlNodePtr xml_node )
{
	zval zv_id;
	zend_string *zs_name = zend_string_init( ( char * ) xml_node->name, xmlStrlen( xml_node->name ), 0 );

	// We seek a and object tags.
	if ( zend_string_equals ( zs_name, MF2_STR( str_a ) ) ) {
		MF2_TRY_ZVAL_XMLATTR( zv_id, xml_node, MF2_STR( str_href ) );
	} else if ( zend_string_equals ( zs_name, MF2_STR( str_object ) ) ) {
		MF2_TRY_ZVAL_XMLATTR( zv_id, xml_node, MF2_STR( str_data ) );
	} else {
		zend_string_free( zs_name );
		return;
	}

	zend_string_free( zs_name );

	if ( IS_NULL == Z_TYPE( zv_id ) ) {
		zval_dtor( &zv_id );
		return;
	}

	// Must begin with # and contain something else too
	if ( 2 > Z_STRLEN( zv_id ) ) {
		zval_dtor( &zv_id );
		return;
	}

	mf2parse_referenced_node_id( object, &zv_id, 1 );

	zval_dtor( &zv_id );
}

/**
 * @since 0.1.0
 */
static void mf2parse_microdata( zval *object, xmlNodePtr xml_node )
{
	zval zv_itemref;
	ZVAL_NULL( &zv_itemref );
	MF2_TRY_ZVAL_XMLATTR( zv_itemref, xml_node, MF2_STR( str_itemref ) );

	if ( IS_NULL != Z_TYPE( zv_itemref ) ) {
		char *search_class = NULL, *last = NULL;
		zval zv_search_class;
		ZVAL_NULL( &zv_search_class );
		search_class = php_strtok_r( Z_STRVAL( zv_itemref ), " ", &last );

		zval zv_classes;
		ZVAL_NULL( &zv_classes );
		MF2_TRY_ZVAL_XMLATTR( zv_classes, xml_node, MF2_STR( str_class ) );

		while( search_class ) {
			ZVAL_STRING( &zv_search_class, search_class );

			mf2parse_referenced_node_id( object, &zv_search_class, 0 );

			search_class = php_strtok_r( NULL, " ", &last );
			zval_dtor( &zv_search_class );
		}

		zval_dtor( &zv_classes );
	}

	zval_dtor( &zv_itemref );
}

/**
 * @since 0.1.0
 */
static void mf2parse_table_headers( zval *object, xmlNodePtr xml_node )
{
	zval zv_id;
	MF2_TRY_ZVAL_XMLATTR( zv_id, xml_node, MF2_STR( str_headers ) );

	if ( IS_NULL == Z_TYPE( zv_id ) ) {
		zval_dtor( &zv_id );
		return;
	}

	mf2parse_referenced_node_id( object, &zv_id, 0 );

	zval_dtor( &zv_id );
}

/**
 * @since 0.1.0
 */
void mf2parse_xml_node( zval *object, xmlNodePtr xml_node, zend_bool no_siblings )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	xmlNodePtr current_node;
	zval zv_mf, *previous_context = NULL;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {

		ZVAL_NULL( &zv_mf );

		switch ( current_node->type ) {
			case XML_ELEMENT_NODE:
				// Include-Pattern, for backcompat roots only
				if ( NULL != mf2parse->context && ( 1 == Z_MF2MFOBJ_P( mf2parse->context )->version ) ) {
					if ( mf2parse_has_include_pattern( object, current_node ) ) {
						mf2parse_include_pattern( object, current_node );
						continue;
					}
				}

				// Microformats parsing - roots
				mf2parse_find_roots( object, &zv_mf, current_node );

				// Microformats parsing - properties
				if ( NULL != mf2parse->context ) {
					mf2parse_find_properties( object, &zv_mf, current_node, IS_NULL != Z_TYPE( zv_mf ) );
				}

				// Rel and Rel-URL parsing
				mf2parse_get_rels( object, current_node );

				// "Time for bed," said Zebedee.
				previous_context = mf2parse->context;

				// "Already?" asked Florence.
				if ( IS_NULL != Z_TYPE( zv_mf ) ) {

					// "It is nearly time for the news, and ..."
					mf2parse->context = &zv_mf;
				}

				// "... there has been enough magic for one day," said Zebedee.
				if ( current_node->children ) {
					mf2parse_xml_node( object, current_node->children, 0 );
				}

				// ZZZzzzZZZzzz ...
				mf2parse_microdata( object, current_node );
				if (
					IS_NULL != Z_TYPE( zv_mf )
					&&
					1 == Z_MF2MFOBJ_P( &zv_mf )->version
					&&
					mf2parse_has_table_headers( object, current_node )
				) {
					mf2parse_table_headers( object, current_node );
				}

				// Good morning!
				mf2parse->context = previous_context;

				if ( IS_NULL != Z_TYPE( zv_mf ) ) {
					// Implied properties
					mf2parse_imply_properties( object, &zv_mf, current_node );

					if ( NULL != mf2parse->context ) {
						mf2microformat_add_child( mf2parse->context, &zv_mf );
					} else {
						zend_hash_next_index_insert_new( mf2parse->items, &zv_mf );
					}
					zval_copy_ctor( &zv_mf );
					Z_ADDREF( zv_mf );
				}
				zval_ptr_dtor( &zv_mf );
			break;

			default:
				// Here to cover all the set in the ENUM and keep the compiler happy.
			break;
		}

		if ( no_siblings ) {
			break;
		}
	}
}

/**
 * @since 0.1.0
 */
void mf2parse_new( zval *object, char *data, size_t data_length, zend_bool data_is_uri )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );

	if ( data_is_uri && !mf2parse->php_base_url ) {
		mf2parse->php_base_url = php_url_parse_ex( data, data_length );
	}

	htmlParserCtxtPtr ctxt = data_is_uri ? htmlCreateFileParserCtxt( data, "UTF8" ) : htmlCreateMemoryParserCtxt( data, data_length );

	if ( !ctxt ) {
		return;
	}

	ctxt->vctxt.error = php_libxml_ctx_error;
	ctxt->vctxt.warning = php_libxml_ctx_warning;
	if ( ctxt->sax != NULL ) {
		ctxt->sax->error = php_libxml_ctx_error;
		ctxt->sax->warning = php_libxml_ctx_warning;
	}

	int html_parsing_context_options = 0;

	if ( mf2parse->options & PHP_MF2_PARSE_NOWARNING ) {
		html_parsing_context_options |= HTML_PARSE_NOWARNING;
	}

	if ( mf2parse->options & PHP_MF2_PARSE_NOERROR ) {
		html_parsing_context_options |= HTML_PARSE_NOERROR;
	}

	if ( mf2parse->options & PHP_MF2_PARSE_RECOVER ) {
		html_parsing_context_options |= HTML_PARSE_RECOVER;
	}

	htmlCtxtUseOptions( ctxt, ( int ) html_parsing_context_options );
	htmlParseDocument( ctxt );
	mf2parse->document = ctxt->myDoc;
	htmlFreeParserCtxt( ctxt );

	mf2parse_resolve_base( object );

	mf2parse_xml_node( object, xmlDocGetRootElement( mf2parse->document ), 0 );
}

#endif /* HAVE_MF2 */
