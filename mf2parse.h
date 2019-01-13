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

#endif /* MF2_PARSE_H */
