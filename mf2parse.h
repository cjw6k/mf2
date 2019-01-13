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

#ifndef MF2_PARSE_H
#define MF2_PARSE_H

#include "php_mf2parse.h"

php_mf2parse_object *mf2parse_fetch_object( zend_object *object );
#define Z_MF2PARSEOBJ_P( zv_object ) mf2parse_fetch_object( Z_OBJ_P( ( zv_object ) ) )

HashTable *mf2parse_get_properties_ht( zval *object, int is_temp );

void mf2parse_new( zval *object, char *data, size_t data_length, zend_bool data_is_uri );
#define mf2parse_new_from_uri( object, uri, uri_length ) mf2parse_new( object, uri, uri_length, 1 )
#define mf2parse_new_from_data( object, data, data_length ) mf2parse_new( object, data, data_length, 0 )

#endif /* MF2_PARSE_H */
