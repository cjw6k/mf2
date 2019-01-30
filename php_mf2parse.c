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

#if HAVE_JSON
#include "ext/json/php_json_parser.h"
#endif

#include "mf2.h"
#include "mf2parse.h"
#include "user_mf2parse.h"

#include "php_mf2parse.h"

zend_class_entry *php_mf2parse_ce;
static zend_object_handlers php_mf2parse_object_handlers;

/**
 * MF2Parse class entry, create_object handler.
 *
 * The create_object handler is run once for each MF2Parse object that is
 * instantiatied. Custom properties are herein initialized.
 *
 * @since 0.1.0
 *
 * @param  zend_class_entry * class_entry  The class entry for the object being
 *                                         created.
 *
 * @return  zend_object *  The embedded standard object of the MF2Parse object.
 */
static zend_object *php_mf2parse_create_object_handler( zend_class_entry *class_entry )
{
	php_mf2parse_object *mf2parse;

	mf2parse = emalloc( sizeof( *mf2parse ) + zend_object_properties_size( class_entry ) );
	memset( mf2parse, 0, sizeof( *mf2parse ) - sizeof( zval ) );

	/* allocate memory for custom properties */
	ALLOC_HASHTABLE( mf2parse->items );
	zend_hash_init( mf2parse->items, 8, NULL, ZVAL_PTR_DTOR, 0 );
	ALLOC_HASHTABLE( mf2parse->rels );
	zend_hash_init( mf2parse->rels, 64, NULL, ZVAL_PTR_DTOR, 0 );
	ALLOC_HASHTABLE( mf2parse->rel_urls );
	zend_hash_init( mf2parse->rel_urls, 128, NULL, ZVAL_PTR_DTOR, 0 );

	ALLOC_HASHTABLE( mf2parse->properties );
	zend_hash_init( mf2parse->properties, 8, NULL, ZVAL_PTR_DTOR, 0 );

	zend_string *tmp;

	tmp = zend_string_init( MF2_REGEX_ROOTS, strlen( MF2_REGEX_ROOTS ), 0 );
	mf2parse->regex_roots = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_ROOTS, strlen( MF2_REGEX_BACKCOMPAT_ROOTS ), 0 );
	mf2parse->regex_backcompat_roots = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_PROPERTIES, strlen( MF2_REGEX_PROPERTIES ), 0 );
	mf2parse->regex_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_ADR_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_ADR_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_adr_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_GEO_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_GEO_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_geo_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HCALENDAR_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HCALENDAR_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hcalendar_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HCARD_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HCARD_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hcard_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HENTRY_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HENTRY_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hentry_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HFEED_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HFEED_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hfeed_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HNEWS_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HNEWS_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hnews_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HPRODUCT_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HPRODUCT_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hproduct_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HREVIEW_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HREVIEW_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hreview_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HRESUME_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HRESUME_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hresume_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_BACKCOMPAT_HREVIEW_AGGREGATE_PROPERTIES, strlen( MF2_REGEX_BACKCOMPAT_HREVIEW_AGGREGATE_PROPERTIES ), 0 );
	mf2parse->regex_backcompat_hreview_aggregate_properties = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_DT_ISO8601, strlen( MF2_REGEX_DT_ISO8601 ), 0 );
	mf2parse->regex_dt_iso8601 = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_DT_TIME, strlen( MF2_REGEX_DT_TIME ), 0 );
	mf2parse->regex_dt_time = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_DT_DAY, strlen( MF2_REGEX_DT_DAY ), 0 );
	mf2parse->regex_dt_day = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	tmp = zend_string_init( MF2_REGEX_DT_TIMEZONE, strlen( MF2_REGEX_DT_TIMEZONE ), 0 );
	mf2parse->regex_dt_timezone = pcre_get_compiled_regex_cache( tmp );
	zend_string_free( tmp );

	mf2parse->context = NULL;

	zend_object_std_init( &mf2parse->zo, class_entry );
	object_properties_init( &mf2parse->zo, class_entry );

	mf2parse->zo.handlers = &php_mf2parse_object_handlers;

	return &mf2parse->zo;
}

/**
 * MF2Parse class entry, dtor_obj handler.
 *
 * The dtor_obj handler is run once, before destroying an MF2Parse object
 * instance. Custom properties are herein destroyed, but their memory is not
 * yet freed.
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The embedded standard object of the MF2Parse
 *                               object to be destroyed.
 */
void php_mf2parse_dtor_object_handler( zend_object *object )
{
	php_mf2parse_object *mf2parse = mf2parse_fetch_object( object );

	/* shutdown custom properties, but not free their memory here */
	zend_hash_destroy( mf2parse->items );
	zend_hash_destroy( mf2parse->rels );
	zend_hash_destroy( mf2parse->rel_urls );
	zend_hash_destroy( mf2parse->properties );

	mf2parse->context = NULL;

	zend_objects_destroy_object( object );
}

/**
 * MF2Parse class entry, free_obj handler.
 *
 * The free_obj handler is run once, in the final step before destroying an
 * MF2Parse object instance. Memory allocated for custom properties is herein
 * freed.
 *
 * @see https://phpinternals.net/categories/zend_objects#free_obj
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The embedded standard object of the MF2Parse
 *                               object to be freed.
 */
void php_mf2parse_free_object_handler( zend_object *object )
{
	php_mf2parse_object *mf2parse = mf2parse_fetch_object( object );

	/* free memory used for custom properties */
	if ( mf2parse->items ) {
		FREE_HASHTABLE( mf2parse->items );
	}

	if ( mf2parse->rels ) {
		FREE_HASHTABLE( mf2parse->rels );
	}

	if ( mf2parse->rel_urls ) {
		FREE_HASHTABLE( mf2parse->rel_urls );
	}

	if ( mf2parse->properties ) {
		FREE_HASHTABLE( mf2parse->properties );
	}

	if ( mf2parse->php_base_url ) {
		php_url_free( mf2parse->php_base_url );
	}

	zval_dtor( &mf2parse->base_url );

	if ( mf2parse->document ) {
		xmlFreeDoc( mf2parse->document );
		xmlCleanupParser();
	}

	zend_object_std_dtor( &mf2parse->zo );
}

/**
 * MF2Parse class entry, get_properties handler.
 *
 * @since 0.1.0
 *
 * @param  zval * object  The subject instance.
 *
 * @return  HashTable *  The properties of the object.
 */
HashTable *php_mf2parse_get_properties_handler( zval *object )
{
	return mf2parse_get_properties_ht( object, 0 );
}

/**
 * MF2Parse class entry, get_debug_info handler.
 *
 * @since 0.1.0
 *
 * @param  zval * object  The subject MF2Parse instance.
 * @param  int * is_temp  Indicates if the return value should be a copy or a
 *                        reference to the memory.
 *
 * @return  HashTable *  The properties of the object.
 */
HashTable *php_mf2parse_get_debug_info_handler( zval *object, int *is_temp )
{
	*is_temp = 1;
	return mf2parse_get_properties_ht( object, 1 );
}

/**
 * Indicates if the instance has the requested member property.
 *
 * @since 0.1.0
 *
 * @param  zval * object       The subject MF2Parse instance.
 * @param  zval * member       The requested member to check.
 * @param  int has_set_exists  0 Check whether the property exists and and is
 *                               not NULL (used by isset).
 *                             1 Check where the property exists and is truthy
 *                             2 Check whether the property exists, even if it
 *                               is NULL
 * @param  int cache_slot      (TODO: No idea what this does).
 *
 * @return  int  0 The requested member does not exist in the subject.
 *               1 The requested member does exist in the subject.
 */
int php_mf2parse_has_property_handler( zval *object, zval *member, int has_set_exists, void **cache_slot )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	int result;
	zval tmp_member;

	result = 0;

	ZVAL_UNDEF( &tmp_member );
	if ( UNEXPECTED( Z_TYPE_P( member ) != IS_STRING ) ) {
		ZVAL_STR( &tmp_member, zval_get_string( member ) );
		member = &tmp_member;
		cache_slot = NULL;
	}

	switch( has_set_exists ) {
		case 1:
			if ( zend_string_equals( Z_STR_P( member ), MF2_STR( str_items ) ) ) {
				result = zend_hash_num_elements( mf2parse->items ) > 0 ? 1 : 0;
			} else if ( zend_string_equals( Z_STR_P( member ), MF2_STR( str_rels ) ) ) {
				result = zend_hash_num_elements( mf2parse->rels ) > 0 ? 1 : 0;
			} else if ( zend_string_equals( Z_STR_P( member ), MF2_STR( str_rel_urls ) ) ) {
				result = zend_hash_num_elements( mf2parse->rel_urls ) > 0 ? 1 : 0;
			} else if ( zend_string_equals( Z_STR_P( member ), MF2_STR( str_relurls ) ) ) {
				result = zend_hash_num_elements( mf2parse->rel_urls ) > 0 ? 1 : 0;
			} else if ( 0 == strcmp( Z_STRVAL_P( member ), "rel-urls" ) ) { // TODO: make that a zend_string
				result = zend_hash_num_elements( mf2parse->rel_urls ) > 0 ? 1 : 0;
			} else {
				result = zend_get_std_object_handlers()->has_property( object, member, has_set_exists, cache_slot );
			}
		break;

		case 0:
		case 2:
			// These properties are never null.
			// Break skipped on purpose.
		default:
			if(
				zend_string_equals( Z_STR_P( member ), MF2_STR( str_items ) )
				||
				zend_string_equals( Z_STR_P( member ), MF2_STR( str_rels ) )
				||
				zend_string_equals( Z_STR_P( member ), MF2_STR( str_rel_urls ) )
				||
				zend_string_equals( Z_STR_P( member ), MF2_STR( str_relurls ) )
				||
				0 == strcmp( Z_STRVAL_P( member ), "rel-urls" )
			){
				result = 1;
			} else {
				result = zend_get_std_object_handlers()->has_property( object, member, has_set_exists, cache_slot );
			}
		break;
	}

	if ( member == &tmp_member ) {
		zval_dtor( member );
	}

	return result;
}

/**
 * @since 0.1.0
 */
zval *php_mf2parse_read_property_handler( zval *object, zval *zv_member, int type, void **cache_slot, zval *zv_return )
{
	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( object );
	zval *zv_result, zv_safe_member;

	zv_result = &EG( uninitialized_zval );

	ZVAL_UNDEF( &zv_safe_member );
	if ( UNEXPECTED( Z_TYPE_P( zv_member ) != IS_STRING ) ) {
		ZVAL_STR( &zv_safe_member, zval_get_string( zv_member ) );
		zv_member = &zv_safe_member;
		cache_slot = NULL;
	}

	if ( zend_string_equals( Z_STR_P( zv_member ), MF2_STR( str_items ) ) ) {
		ZVAL_ARR( zv_return, mf2parse->items );
	} else if ( zend_string_equals( Z_STR_P( zv_member ), MF2_STR( str_rels ) ) ) {
		ZVAL_ARR( zv_return, mf2parse->rels );
	} else if (
		zend_string_equals( Z_STR_P( zv_member ), MF2_STR( str_rel_urls ) )
		||
		zend_string_equals( Z_STR_P( zv_member ), MF2_STR( str_relurls ) )
		||
		0 == strcmp( "rel-urls", ZSTR_VAL( Z_STR_P( zv_member ) ) )
	){
		ZVAL_ARR( zv_return, mf2parse->rel_urls );
	} else {
		zv_result = zend_get_std_object_handlers()->read_property( object, zv_member, type, cache_slot, zv_return );
		if ( zv_member == &zv_safe_member ) {
			zval_dtor( zv_member );
		}

		return zv_result;
	}

	zval_copy_ctor( zv_return );

	if ( zv_member == &zv_safe_member ) {
		zval_dtor( zv_member );
	}

	return zv_return;
}

#if HAVE_JSON
ZEND_BEGIN_ARG_INFO( arginfo_mf2parse_jsonSerialize, 0 )
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO_EX( arginfo_mf2parse_construct, 0, 0, 1 )
	ZEND_ARG_TYPE_INFO( 0, data, IS_STRING, 0 )
	ZEND_ARG_TYPE_INFO( 0, base_url, IS_STRING, 1 )
	ZEND_ARG_TYPE_INFO( 0, data_is_uri, _IS_BOOL, 1 )
	ZEND_ARG_TYPE_INFO( 0, options, IS_LONG, 1 )
ZEND_END_ARG_INFO()

static const zend_function_entry php_mf2parse_functions[] = {
	PHP_ME( MF2Parse, __construct, arginfo_mf2parse_construct, ZEND_ACC_PUBLIC )
#if HAVE_JSON
	PHP_ME( MF2Parse, jsonSerialize, arginfo_mf2parse_jsonSerialize, ZEND_ACC_PUBLIC )
#endif
	PHP_FE_END
};

/**
 * Initialize the MF2Parse class entry once, when the extension is first loaded
 * by a PHP instance.
 *
 * @since 0.1.0
 */
PHP_MINIT_FUNCTION( mf2parse )
{
	zend_class_entry temp_ce;

	INIT_CLASS_ENTRY( temp_ce, "MF2Parse", php_mf2parse_functions );
	php_mf2parse_ce = zend_register_internal_class( &temp_ce );

#if HAVE_JSON
	zend_class_implements( php_mf2parse_ce, 1, php_json_serializable_ce );
#endif

	php_mf2parse_ce->create_object = php_mf2parse_create_object_handler;
	memcpy( &php_mf2parse_object_handlers, zend_get_std_object_handlers(), sizeof( php_mf2parse_object_handlers ) );

	php_mf2parse_object_handlers.free_obj       = php_mf2parse_free_object_handler;
	php_mf2parse_object_handlers.dtor_obj       = php_mf2parse_dtor_object_handler;
	php_mf2parse_object_handlers.clone_obj      = NULL;
	php_mf2parse_object_handlers.get_properties = php_mf2parse_get_properties_handler;
	php_mf2parse_object_handlers.get_debug_info = php_mf2parse_get_debug_info_handler;
	php_mf2parse_object_handlers.has_property   = php_mf2parse_has_property_handler;
	php_mf2parse_object_handlers.read_property  = php_mf2parse_read_property_handler;

	php_mf2parse_object_handlers.offset = XtOffsetOf( php_mf2parse_object, zo );

	return SUCCESS;
}

#endif /* HAVE_MF2 */
