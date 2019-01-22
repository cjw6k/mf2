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

#ifndef PHP_MF2MICROFORMAT_H
#define PHP_MF2MICROFORMAT_H

typedef struct _php_mf2microformat_object {
	zend_ulong version;
	zend_bool has_p_prop, has_u_prop, has_dt_prop, has_e_prop, has_nested_roots;
	zval contexts;
	zend_object zo;
} php_mf2microformat_object;

extern zend_class_entry *php_mf2microformat_ce;

PHP_MINIT_FUNCTION( mf2microformat );

#endif /* PHP_MF2MICROFORMAT_H */