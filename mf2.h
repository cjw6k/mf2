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

#ifndef MF2_H
#define MF2_H

#include "mf2_str_defs.h"

typedef struct _mf2_str_globals {
#define X(str) zend_string *str_ ## str;
	MF2_STR_DEFS
#undef X
} mf2_str_globals;

mf2_str_globals str_globals_mf2;

#define MF2_STR(str) str_globals_mf2.str

#endif /* MF2_H */
