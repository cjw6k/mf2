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

#include "zend_smart_str.h"

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
 * @param  zval *object   The subject microformat.
 * @param  zval *zv_type  The vocabulary type to add.
 */
void mf2microformat_add_type( zval *object, zval *zv_type)
{
	zval *zv_current_types = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_type ) ), ZSTR_LEN( MF2_STR( str_type ) ), 0, NULL );
	add_next_index_string( zv_current_types, Z_STRVAL_P( zv_type ) );
	zend_hash_sort( Z_ARRVAL_P( zv_current_types ), mf2_strcasecmp, 1 );
}

/**
 * Add a backcompat type to the set of types used by this microformat.
 *
 * The microformats vocabularies are represented by the label 'type' in the
 * standard representation of the parse. Backcompat microformats are sometimes
 * referred to as Classic Microformats.
 *
 * @link http://microformats.org/wiki/Main_Page#Specifications
 *
 * @since 0.1.0
 *
 * @param  zval *object   The subject microformat.
 * @param  zval *zv_type  The backcompat vocabulary type to add.
 */
void mf2microformat_add_backcompat_type( zval *object, zval *zv_type)
{
	add_next_index_string( &Z_MF2MFOBJ_P( object )->backcompat_types, Z_STRVAL_P( zv_type ) );

	zval *zv_current_types = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_type ) ), ZSTR_LEN( MF2_STR( str_type ) ), 0, NULL );

	smart_str ss_type = {0};
	smart_str_appends( &ss_type, "h-" );

	/** hCard.
	 * @link http://microformats.org/wiki/hCard */
	if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_vcard ) ) ) {
		smart_str_appends( &ss_type, "card" );

	/** hAtom.
	 * @link http://microformats.org/wiki/hAtom */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hfeed ) ) ) {
		smart_str_appends( &ss_type, "feed" );
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hentry ) ) ) {
		smart_str_appends( &ss_type, "entry" );

	/** hNews.
	 * @link http://microformats.org/wiki/hNews */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hnews ) ) ) {
		smart_str_appends( &ss_type, "news" );

	/** hCalendar.
	 * @link http://microformats.org/wiki/hCalendar */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_vevent ) ) ) {
		smart_str_appends( &ss_type, "event" );

	/** hProduct.
	 * @link http://microformats.org/wiki/hProduct */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hproduct ) ) ) {
		smart_str_appends( &ss_type, "product" );

	/** hReview.
	 * @link http://microformats.org/wiki/hReview */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hreview ) ) ) {
		smart_str_appends( &ss_type, "review" );

	/** hreview-aggregate.
	 * @link http://microformats.org/wiki/hreview-aggregate */
	} else if ( 0 == strcasecmp( Z_STRVAL_P( zv_type ), "hreview-aggregate" ) ) {
		smart_str_appends( &ss_type, "review-aggregate" );

	/** hResume.
	 * @link http://microformats.org/wiki/hResume */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hresume ) ) ) {
		smart_str_appends( &ss_type, "resume" );

	/** hRecipe.
	 * @link http://microformats.org/wiki/hRecipe */
	} else if ( zend_string_equals( Z_STR_P( zv_type ), MF2_STR( str_hrecipe ) ) ) {
		// smart_str_appends( &ss_type, "recipe" );

	/** adr, geo.
	 * @link http://microformats.org/wiki/adr
	 * @link http://microformats.org/wiki/geo */
	} else {
		smart_str_appends( &ss_type, Z_STRVAL_P( zv_type ) );
	}

	smart_str_0( &ss_type );

	add_next_index_string( zv_current_types, ZSTR_VAL( ss_type.s ) );
	zend_hash_sort( Z_ARRVAL_P( zv_current_types ), mf2_strcasecmp, 1 );

	smart_str_free( &ss_type );
}

/**
 * @since 0.1.0
 */
zval *mf2microformat_get_backcompat_types( zval *object )
{
	return &Z_MF2MFOBJ_P( object )->backcompat_types;
}

/**
 * @since 0.1.0
 */
void mf2microformat_add_property( zval *object, zval *zv_key, zval *zv_value )
{
	zval *zv_current_properties = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), 0, NULL );
	zval *zv_current_value = zend_hash_find( Z_ARRVAL_P( zv_current_properties ), Z_STR_P( zv_key ) );

	if( NULL == zv_current_value ) {
		zval zv_properties;
		array_init( &zv_properties );
		add_assoc_zval_ex( zv_current_properties, Z_STRVAL_P( zv_key ), Z_STRLEN_P( zv_key ), &zv_properties );
		zv_current_value = &zv_properties;
	}

	add_next_index_zval( zv_current_value, zv_value );

	zval_copy_ctor( zv_value );
}

/**
 * @since 0.1.0
 */
static void mf2microformat_set_id( zval *object, xmlNodePtr xml_node )
{
	if ( ! xmlHasProp ( xml_node, ( xmlChar * ) ZSTR_VAL( MF2_STR( str_id ) ) ) ) {
		return;
	}

	zval zv_id;
	MF2_ZVAL_XMLATTR( zv_id, xml_node, MF2_STR( str_id ) );
	add_property_zval( object, ZSTR_VAL( MF2_STR( str_id ) ), &zv_id );
	zval_dtor( &zv_id );
}

/**
 * @since 0.1.0
 */
void mf2microformat_new( zval *object, xmlNodePtr xml_node )
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

	mf2microformat_set_id( object, xml_node );

	php_mf2microformat_object *mf2mf = Z_MF2MFOBJ_P( object );
	mf2mf->has_p_prop = mf2mf->has_u_prop = mf2mf->has_dt_prop = mf2mf->has_e_prop = 0;
	mf2mf->has_nested_roots = 0;
}

/**
 * @since 0.1.0
 */
zend_bool mf2microformat_has_property( zval *object, zend_string *zv_key )
{
	zval *zv_properties = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), 1, NULL );
	if ( IS_ARRAY != Z_TYPE_P( zv_properties ) ) {
		return 0;
	}

	return zend_hash_exists( Z_ARRVAL_P( zv_properties ), zv_key );
}

/**
 * @since 0.1.0
 */
void mf2microformat_get_property( zval *object, zend_string *zv_key, zval *zv_return_value )
{
	zval *zv_properties = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), 1, NULL );
	if ( IS_ARRAY != Z_TYPE_P( zv_properties ) ) {
		ZVAL_NULL( zv_return_value );
	}

	zv_return_value = zend_hash_find( Z_ARRVAL_P( zv_properties ), zv_key );
}

/**
 * @since 0.1.0
 */
zend_bool mf2microformat_has_children( zval *object )
{
	return (
		1 == Z_MF2MFOBJ_P( object )->has_nested_roots
		||
		IS_NULL != Z_TYPE_P( zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_children ) ), ZSTR_LEN( MF2_STR( str_children ) ), 1, NULL ) )
	);
}

/**
 * @since 0.1.0
 */
static void mf2microformat_add_nested_child( zval *object, zval *zv_child )
{
	Z_MF2MFOBJ_P( object )->has_nested_roots = 1;

	zval *zv_parent_properties = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), 1, NULL );
	zval *zv_child_properties = zend_read_property( php_mf2microformat_ce, zv_child, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), 1, NULL );

	zval *zv_prefix, *zv_name, *zv_parent_property, *context, *zv_source;
	ZEND_HASH_FOREACH_VAL( Z_ARRVAL( Z_MF2MFOBJ_P( zv_child )->contexts ), context ) {
		zv_prefix = zend_hash_index_find( Z_ARRVAL_P( context ), 0 );

		// TODO: faster?

		if( zend_string_equals( MF2_STR( str_p ), Z_STR_P( zv_prefix ) ) ) {
			zv_source = zend_hash_find( Z_ARRVAL_P( zv_child_properties ), MF2_STR( str_name ) );
		} else if( zend_string_equals( MF2_STR( str_u ), Z_STR_P( zv_prefix ) ) ) {
			zv_source = zend_hash_find( Z_ARRVAL_P( zv_child_properties ), MF2_STR( str_url ) );
		} else if( zend_string_equals( MF2_STR( str_dt ), Z_STR_P( zv_prefix ) ) ) {

		} else if( zend_string_equals( MF2_STR( str_e ), Z_STR_P( zv_prefix ) ) ) {

		}

		zv_name = zend_hash_index_find( Z_ARRVAL_P( context ), 1 );
		zv_parent_property = zend_hash_find( Z_ARRVAL_P( zv_parent_properties ), Z_STR_P( zv_name ) );

		// The final entry in the property on the parent is the one to replace with this nested root
		zend_hash_internal_pointer_end( Z_ARRVAL_P( zv_parent_property ) );
		zval zv_replace_key;
		zend_hash_get_current_key_zval( Z_ARRVAL_P( zv_parent_property ), &zv_replace_key );

		if ( NULL == zv_source ) {
			mf2microformat_add_value( zv_child, zend_hash_get_current_data( Z_ARRVAL_P( zv_parent_property ) ) );
		} else {
			mf2microformat_add_value( zv_child, zend_hash_index_find( Z_ARRVAL_P( zv_source ), 0 ) );
		}

		array_set_zval_key( Z_ARRVAL_P( zv_parent_property ), &zv_replace_key, zv_child );

	} ZEND_HASH_FOREACH_END();
}

/**
 * @since 0.1.0
 */
void mf2microformat_add_child( zval *object, zval *zv_child )
{
	if ( zend_hash_num_elements( Z_ARRVAL( Z_MF2MFOBJ_P( zv_child )->contexts ) ) ) {
		mf2microformat_add_nested_child( object, zv_child );
		Z_DELREF_P( zv_child );
		return;
	}

	zval *zv_current_children = zend_read_property( php_mf2microformat_ce, object, ZSTR_VAL( MF2_STR( str_children ) ), ZSTR_LEN( MF2_STR( str_children ) ), 1, NULL );

	if ( IS_NULL == Z_TYPE_P(zv_current_children) ) {
		zval zv_children;
		array_init( &zv_children );
		add_property_zval( object, ZSTR_VAL( MF2_STR( str_children ) ), &zv_children );
		zv_current_children = &zv_children;
		Z_DELREF( zv_children );
	}

	add_next_index_zval( zv_current_children, zv_child );
}

/**
 * @since 0.1.0
 */
void mf2microformat_add_value( zval *object, zval *zv_value )
{
	add_property_zval( object, ZSTR_VAL( MF2_STR( str_value ) ), zv_value );
}

#endif /* HAVE_MF2 */
