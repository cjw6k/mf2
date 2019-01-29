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
#include "mf2microformat.h"
#include "user_mf2microformat.h"

#include "php_mf2microformat.h"

zend_class_entry *php_mf2microformat_ce;
static zend_object_handlers php_mf2microformat_object_handlers;

/**
 * MF2Microformat class entry, create_object handler.
 *
 * The create_object handler is run once for each MF2Microformat object that is
 * instantiatied. Custom properties are herein initialized.
 *
 * @since 0.1.0
 *
 * @param  zend_class_entry * class_entry  The class entry for the object being
 *                                         created.
 *
 * @return  zend_object *  The embedded standard object of the MF2Microformat
 *                         object.
 */
static zend_object *php_mf2microformat_create_object_handler( zend_class_entry *class_entry )
{
	php_mf2microformat_object *mf2mf;

	mf2mf = emalloc( sizeof( *mf2mf ) + zend_object_properties_size( class_entry ) );
	memset( mf2mf, 0, sizeof( *mf2mf ) - sizeof( zval ) );

	/* allocate memory for custom properties */
	array_init( &mf2mf->backcompat_types );
	array_init( &mf2mf->contexts );

	ZVAL_NULL( &mf2mf->date_context );

	zend_object_std_init( &mf2mf->zo, class_entry );
	object_properties_init( &mf2mf->zo, class_entry );

	mf2mf->zo.handlers = &php_mf2microformat_object_handlers;

	return &mf2mf->zo;
}

/**
 * MF2Microformat class entry, dtor_obj handler.
 *
 * The dtor_obj handler is run once, before destroying an MF2Microformat object
 * instance. Custom properties are herein destroyed, but their memory is not
 * yet freed.
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The embedded standard object of the
 *                               MF2Microformat object to be destroyed.
 */
void php_mf2microformat_dtor_object_handler( zend_object *object )
{
	//php_mf2microformat_object *mf2mf = mf2microformat_fetch_object( object );

	/* shutdown custom properties, but not free their memory here */

	zend_objects_destroy_object( object );
}

/**
 * MF2Microformat class entry, free_obj handler.
 *
 * The free_obj handler is run once, in the final step before destroying an
 * MF2Microformat object instance. Memory allocated for custom properties is
 * herein freed.
 *
 * @see https://phpinternals.net/categories/zend_objects#free_obj
 *
 * @since 0.1.0
 *
 * @param  zend_object * object  The embedded standard object of the
 *                               MF2Microformat object to be freed.
 */
void php_mf2microformat_free_object_handler( zend_object *object )
{
	php_mf2microformat_object *mf2mf = mf2microformat_fetch_object( object );

	/* free memory used for custom properties */
	zval_ptr_dtor( &mf2mf->backcompat_types );
	zval_ptr_dtor( &mf2mf->contexts );
	zval_ptr_dtor( &mf2mf->date_context );

	zend_object_std_dtor( &mf2mf->zo );
}

static const zend_function_entry php_mf2microformat_functions[] = {
	PHP_ME( MF2Microformat, __construct, NULL, ZEND_ACC_PUBLIC )
	PHP_FE_END
};

/**
 * Initialize the MF2Microformat class entry once, when the extension is first
 * loaded by a PHP instance.
 *
 * @since 0.1.0
 */
PHP_MINIT_FUNCTION( mf2microformat )
{
	zend_class_entry temp_ce;

	INIT_CLASS_ENTRY( temp_ce, "MF2Microformat", php_mf2microformat_functions );
	php_mf2microformat_ce = zend_register_internal_class( &temp_ce );

	php_mf2microformat_ce->create_object = php_mf2microformat_create_object_handler;
	memcpy( &php_mf2microformat_object_handlers, zend_get_std_object_handlers(), sizeof( php_mf2microformat_object_handlers ) );

	php_mf2microformat_object_handlers.free_obj  = php_mf2microformat_free_object_handler;
	php_mf2microformat_object_handlers.dtor_obj  = php_mf2microformat_dtor_object_handler;
	php_mf2microformat_object_handlers.clone_obj = NULL;

	php_mf2microformat_object_handlers.offset = XtOffsetOf( php_mf2microformat_object, zo );

	zend_declare_property_null( php_mf2microformat_ce, ZSTR_VAL( MF2_STR( str_type ) ), ZSTR_LEN( MF2_STR( str_type ) ), ZEND_ACC_PUBLIC );
	zend_declare_property_null( php_mf2microformat_ce, ZSTR_VAL( MF2_STR( str_properties ) ), ZSTR_LEN( MF2_STR( str_properties ) ), ZEND_ACC_PUBLIC );

	return SUCCESS;
}

#endif /* HAVE_MF2 */
