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

static const zend_module_dep mf2_deps[] = {
	ZEND_MOD_END
};

static const zend_function_entry mf2_functions[] = {
	PHP_FE_END
};

/**
 * Initialize the extension once, when it is first loaded by a PHP instance.
 *
 * @since 0.1.0
 */
PHP_MINIT_FUNCTION( mf2 )
{
	return SUCCESS;
}

/**
 * Shutdown the extension when it is unloaded by a PHP, at final shutdown.
 *
 * @since 0.1.0
 */
PHP_MSHUTDOWN_FUNCTION( mf2 )
{
	return SUCCESS;
}

/**
 * A callback function triggered when phpinfo() is run.
 *
 * @since 0.1.0
 */
PHP_MINFO_FUNCTION( mf2 )
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Microformats2 support", "enabled");
	php_info_print_table_end();
}

zend_module_entry mf2_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	mf2_deps,
	"mf2",
	mf2_functions,
	PHP_MINIT( mf2 ),
	PHP_MSHUTDOWN( mf2 ),
	NULL,
	NULL,
	PHP_MINFO( mf2 ),
	PHP_MF2_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MF2
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE( mf2 )
#endif

#endif /* HAVE_MF2 */