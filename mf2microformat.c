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

#include "mf2.h"
#include "php_mf2microformat.h"

#include "mf2microformat.h"

/**
 * Convert a standard zend_object reference to an MF2Microformat object
 * reference.
 *
 * A standard zend_object is embedded within each MF2Microformat object. Many
 * API functions expect a zend_object parameter, making this function helpful
 * to reference the containing MF2Parse object of the standard zend_object
 * passed by the API.
 *
 * @link https://phpinternals.net/categories/zend_objects#offset
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The reference to a standard zend_object.
 *
 * @return  mf2microformat_object *  The containing MF2Microformat object.
 */
php_mf2microformat_object *mf2microformat_fetch_object( zend_object *object )
{
	return ( php_mf2microformat_object * ) ( ( char * ) ( object ) - XtOffsetOf( php_mf2microformat_object, zo ) );
}

/**
 * Add a type to the set of types used by this microformat.
 *
 * The microformats vocabularies are represented by the label 'type' in the
 * standard representation of the parse.
 *
 * @link http://microformats.org/wiki/microformats2#v2_vocabularies
 *
 * @since 0.1.0
 *
 * @param  zval *object      The subject microformat.
 * @param  zval *vocabulary  The vocabulary to add.
 */
void mf2microformat_add_type( zval *object, zval *type)
{
	zval *zv_current_types = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_type ) ), ZSTR_LEN( MF2_STR( str_type ) ), 0, NULL );

	add_next_index_string( zv_current_types, Z_STRVAL_P( type ) );

	zend_hash_sort( Z_ARRVAL_P( zv_current_types ), mf2_strcasecmp, 1 );
}

/**
 * @since 0.1.0
 */
void mf2microformat_new( zval *object )
{
	object_init_ex( object, php_mf2microformat_ce );
	Z_DELREF_P( object );

	zval zv_type, zv_properties;

	array_init( &zv_type );
	Z_DELREF( zv_type );
	zend_update_property_ex( php_mf2microformat_ce, object, MF2_STR( str_type ), &zv_type );

	array_init( &zv_properties );
	Z_DELREF( zv_properties );
	zend_update_property_ex( php_mf2microformat_ce, object, MF2_STR( str_properties ), &zv_properties );
}


#endif /* HAVE_MF2 */
