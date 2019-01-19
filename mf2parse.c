/*
  +----------------------------------------------------------------------+
  | mf2: extension for PHP                                                |
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
#include <libxml/xpath.h>

#include "ext/libxml/php_libxml.h"

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
	smart_str_appends(&smart_uri_str, scheme_separator);

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
			smart_str_appends( &smart_uri_str, mf2parse->php_base_url->path );
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

	if( relative_url_parts->query ) {
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

	if( NULL == doc_url_parts ) {
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

	php_url *url_parts = php_url_parse( Z_STRVAL( zv_href ) );
	if ( NULL != url_parts ) {
		if ( mf2_is_relative_url( url_parts ) ) {
			mf2parse_resolve_relative_uri( object, &zv_href, url_parts );
		}
		php_url_free( url_parts );
	}

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
		if( !mf2_in_array( rels_ptr, &zv_rel ) ) {
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

	xmlFree(rel);
	xmlFree(href);
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
static void mf2parse_find_roots( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if( ! xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) ) ) {
		return;
	}

	xmlChar *classes = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) );

	zval zv_classes;
	ZVAL_STRING( &zv_classes, ( char * ) classes );

	// Microformats2 root parsing
	if ( ! mf2parse_find_v2_roots( object, zv_mf, xml_node, &zv_classes ) ) {

		// Backcompat root parsing
		//mf2parse_find_backcompat_roots( object, mf, xml_node );
	}

	zval_dtor( &zv_classes );
	xmlFree( classes );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_v2_properties( zval *object, zval *zv_mf, xmlNodePtr xml_node, zval *zv_classes )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval matched, matches;

	ZVAL_NULL( &matched );
	ZVAL_NULL( &matches );

	// Microformats2 Properties
	php_pcre_match_impl( mf2parse->regex_properties, Z_STRVAL_P( zv_classes ), Z_STRLEN_P( zv_classes ), &matched, &matches, 1, 1, Z_L( 2 ), Z_L( 0 ) );

	if ( ! ( Z_LVAL( matched ) > 0 ) || IS_ARRAY != Z_TYPE( matches ) ) {
		zval_ptr_dtor( &matched );
		zval_ptr_dtor( &matches );

		return;
	}

	php_mf2microformat_object *mf2mf = Z_MF2MFOBJ_P( zv_mf );

	zval *zv_prefix, *zv_name, *match_arr, zv_property;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( matches ), match_arr ) {
		zv_prefix = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 1 );
		zv_name   = zend_hash_index_find( Z_ARRVAL_P( match_arr ), 2 );

		array_init( &zv_property );

		zend_hash_clean( Z_ARRVAL( zv_property ) );

		// TODO: switch on the string's hash values

		if ( zend_string_equals( MF2_STR( str_p ), Z_STR_P( zv_prefix ) ) ) {
			// parse a p-* property
			mf2mf->has_p_prop = 1;

			// TODO: higher priority checks
			xmlBufferPtr buffer = xmlBufferCreate();
			xmlNodeBufGetContent( buffer, xml_node );

			// TODO remove script & style, replace img with alt
			zval zv_buffer;
			ZVAL_STRING( &zv_buffer, ( char * ) buffer->content );
			mf2_trim_html_space_chars( &zv_buffer, Z_STRVAL( zv_buffer ) );

			add_next_index_string( &zv_property, Z_STRVAL( zv_buffer ) );

			zval_dtor( &zv_buffer );
			xmlBufferFree( buffer );

			mf2microformat_add_property( zv_mf, zv_name, &zv_property );

		} else if ( zend_string_equals( MF2_STR( str_u ), Z_STR_P( zv_prefix ) ) ) {
			// parse a u-* property
			mf2mf->has_u_prop = 1;
		} else if ( zend_string_equals( MF2_STR( str_dt ), Z_STR_P( zv_prefix ) ) ) {
			mf2mf->has_dt_prop = 1;
		} else if ( zend_string_equals( MF2_STR( str_e ), Z_STR_P( zv_prefix ) ) ) {
			mf2mf->has_e_prop = 1;
		}

		zval_ptr_dtor( &zv_property );
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor( &matched );
	zval_ptr_dtor( &matches );
}

/**
 * @since 0.1.0
 */
static void mf2parse_find_properties( zval *object, zval *zv_mf, xmlNodePtr xml_node )
{
	if( ! xmlHasProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) ) ) {
		return;
	}

	xmlChar *classes = xmlGetProp( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_class ) ) );

	zval zv_classes;
	ZVAL_STRING( &zv_classes, ( char * ) classes );

	php_mf2microformat_object *mf2mf = Z_MF2MFOBJ_P( zv_mf );

	if ( 2 == mf2mf->version ) {
		// Microformats2 property parsing
		mf2parse_find_v2_properties( object, zv_mf, xml_node, &zv_classes );
	} else {
		// Backcompat property parsing
		//mf2parse_find_backcompat_properties( object, mf, xml_node );
	}

	zval_dtor( &zv_classes );
	xmlFree( classes );
}

/**
 * @since 0.1.0
 */
static void mf2parse_xml_node( zval *object, xmlNodePtr xml_node )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	xmlNodePtr current_node;
	zval zv_mf;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {

		ZVAL_NULL( &zv_mf );

		switch ( current_node->type ) {
			case XML_ELEMENT_NODE:
				// Microformats parsing - roots
				mf2parse_find_roots( object, &zv_mf, current_node );

				// Microformats parsing - properties
				if ( NULL != mf2parse->context ) {
					mf2parse_find_properties( object, mf2parse->context, current_node );
				}

				// Rel and Rel-URL parsing
				mf2parse_get_rels( object, current_node );

				// Recurse
				if ( IS_NULL != Z_TYPE( zv_mf ) ) {
					mf2parse->context = &zv_mf;
				}
				mf2parse_xml_node( object, current_node->children );

				if ( IS_NULL != Z_TYPE( zv_mf ) ) {
					zend_hash_next_index_insert_new( mf2parse->items, &zv_mf );
					zval_copy_ctor( &zv_mf );
					Z_ADDREF( zv_mf );
				}
				zval_ptr_dtor( &zv_mf );
			break;

			default:
				// Here to cover all the set in the ENUM and keep the compiler happy.
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

	htmlParserCtxtPtr ctxt = data_is_uri ? htmlCreateFileParserCtxt( data, NULL ) : htmlCreateMemoryParserCtxt( data, data_length );

	if( !ctxt ) {
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

	mf2parse_xml_node( object, xmlDocGetRootElement( mf2parse->document ) );
}

#endif /* HAVE_MF2 */
