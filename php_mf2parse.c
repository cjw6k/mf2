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

#include "php_mf2.h"

#include "php_mf2parse.h"

static zend_class_entry *mf2parse_ce;
static zend_object_handlers mf2parse_object_handlers;

static const zend_function_entry mf2parse_functions[] = {
	PHP_FE_END
};

typedef struct _mf2parse_object {
	zend_object zo;
} mf2parse_object;

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
static mf2parse_object *php_mf2parse_fetch_object( zend_object *object )
{
	return ( mf2parse_object * ) ( ( char * ) ( object ) - XtOffsetOf( mf2parse_object, zo ) );
}

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
static zend_object *mf2parse_create_object_handler( zend_class_entry *class_entry )
{
	mf2parse_object *mf2parse;

	mf2parse = emalloc( sizeof( *mf2parse ) + zend_object_properties_size( class_entry ) );
	memset( mf2parse, 0, sizeof( *mf2parse ) - sizeof( zval ) );

	/* allocate memory for custom properties */

	zend_object_std_init( &mf2parse->zo, class_entry );
	object_properties_init( &mf2parse->zo, class_entry );

	mf2parse->zo.handlers = &mf2parse_object_handlers;

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
void mf2parse_dtor_object_handler( zend_object *object )
{
	//mf2parse_object *mf2parse = php_mf2parse_fetch_object( object );

	/* shutdown custom properties, but not free their memory here */

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
void mf2parse_free_object_handler( zend_object *object )
{
	mf2parse_object *mf2parse = php_mf2parse_fetch_object( object );

	/* free memory used for custom properties */

	zend_object_std_dtor( &mf2parse->zo );
}

/**
 * Initialize the MF2Parse class entry once, when the extension is first loaded
 * by a PHP instance.
 *
 * @since 0.1.0
 */
PHP_MINIT_FUNCTION( mf2parse )
{
	zend_class_entry temp_ce;
	zval zv_null;
	ZVAL_NULL( &zv_null );

	INIT_CLASS_ENTRY( temp_ce, "Mf2Parse", mf2parse_functions );
	mf2parse_ce = zend_register_internal_class( &temp_ce );

	mf2parse_ce->create_object = mf2parse_create_object_handler;
	memcpy( &mf2parse_object_handlers, zend_get_std_object_handlers(), sizeof( mf2parse_object_handlers ) );

	mf2parse_object_handlers.free_obj  = mf2parse_free_object_handler;
	mf2parse_object_handlers.dtor_obj  = mf2parse_dtor_object_handler;
	mf2parse_object_handlers.clone_obj = NULL;

	mf2parse_object_handlers.offset = XtOffsetOf( mf2parse_object, zo );

	return SUCCESS;
}

#endif /* HAVE_MF2 */
