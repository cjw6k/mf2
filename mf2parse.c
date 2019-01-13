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

#include "ext/libxml/php_libxml.h"

#include "mf2.h"
#include "php_mf2parse.h"

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
static void mf2parse_add_rel( zval *object, char *rel, char *href, xmlNodePtr xml_node )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval zv_arr_rels, zv_arr_rel_urls, zv_arr_prop_rels, zv_rel, zv_href, *rels_ptr, *rel_urls_ptr;
	xmlChar *attr;

	ZVAL_STRING( &zv_rel, rel );
	ZVAL_STRING( &zv_href, href );
	
	mf2_trim_html_space_chars( &zv_href, Z_STRVAL(zv_href) );

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
static void mf2parse_xml_node( zval *object, xmlNodePtr xml_node )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	xmlNodePtr current_node;

	for ( current_node = xml_node; current_node; current_node = current_node->next ) {
		switch ( current_node->type ) {
			case XML_ELEMENT_NODE:
				// TODO: microformats2 parsing

				// Rel and Rel-URL parsing
				mf2parse_get_rels( object, current_node );

				// Recurse
				mf2parse_xml_node( object, current_node->children );


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

	htmlParserCtxtPtr ctxt = data_is_uri ? htmlCreateFileParserCtxt( data, NULL ) : htmlCreateMemoryParserCtxt( data, data_length );

	if( !ctxt ) {
		return;
	}

	if ( 0 != mf2parse->options ) {
		htmlCtxtUseOptions( ctxt, ( int ) mf2parse->options );
	}

	htmlParseDocument( ctxt );
	mf2parse->document = ctxt->myDoc;
	htmlFreeParserCtxt( ctxt );

	mf2parse_xml_node( object, xmlDocGetRootElement( mf2parse->document ) );
}

#endif /* HAVE_MF2 */
