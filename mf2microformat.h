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

#ifndef MF2_MICROFORMAT_H
#define MF2_MICROFORMAT_H

#include "ext/libxml/php_libxml.h"

#include "php_mf2microformat.h"

php_mf2microformat_object *mf2microformat_fetch_object( zend_object *object );
#define Z_MF2MFOBJ_P( zv_object ) mf2microformat_fetch_object( Z_OBJ_P( ( zv_object ) ) )

void mf2microformat_new( zval *object, xmlNodePtr xml_node );
void mf2microformat_add_type( zval *object, zval *type );
void mf2microformat_add_property( zval *object, zval *zv_key, zval *zv_value );

#endif /* MF2_MICROFORMAT_H */
