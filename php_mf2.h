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

#ifndef PHP_MF2_H
#define PHP_MF2_H

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_MF2_VERSION "0.1.0"

extern zend_module_entry php_mf2_module_entry;
#define phpext_mf2_ptr &php_mf2_module_entry

#endif /* PHP_MF2 */