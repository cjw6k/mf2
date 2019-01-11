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

#if HAVE_MF2

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_MF2_VERSION "0.1.0"

extern zend_module_entry mf2_module_entry;
#define mf2_module_ptr &mf2_module_entry

#define MF2G(v) ZEND_MODULE_GLOBALS_ACCESSOR(mf2, v)

#else
#define mf2_module_ptr NULL
#endif /* HAVE_MF2 */

#define phpext_mf2_ptr mf2_module_ptr

#endif /* PHP_MF2 */