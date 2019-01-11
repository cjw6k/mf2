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

static zend_object_handlers mf2parse_object_handlers;

typedef struct _mf2parse_object {
	zend_object zo;
} mf2parse_object;

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

void mf2parse_dtor_object_handler( zend_object *object )
{
	//mf2parse_object *mf2parse = ( mf2parse_object * )( ( char* )( object ) - XtOffsetOf( mf2parse_object, zo ) );

	/* shutdown custom properties, but not free their memory here */

	zend_objects_destroy_object( object );
}

void mf2_parse_free_object_handler(zend_object *object)
{
	mf2parse_object *mf2parse = ( mf2parse_object * )( ( char* )( object ) - XtOffsetOf( mf2parse_object, zo ) );

	/* free memory used for custom properties */

	zend_object_std_dtor( &mf2parse->zo );
}

const zend_function_entry mf2parse_functions[] = {
	PHP_FE_END
};

PHP_MINIT_FUNCTION( mf2parse )
{
	zend_class_entry temp_ce;
	zval zv_null;
	ZVAL_NULL( &zv_null );

	INIT_CLASS_ENTRY( temp_ce, MF2_STR( str_MF2Parse ), mf2parse_functions );
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
