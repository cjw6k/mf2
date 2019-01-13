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

#include "ext/standard/info.h"

#include "mf2.h"
#include "user_mf2.h"
#include "php_mf2parse.h"

#include "php_mf2.h"

static const zend_module_dep php_mf2_deps[] = {
	ZEND_MOD_REQUIRED( "libxml" )
	ZEND_MOD_END
};

/**
 * Initialize the extension once, when it is first loaded by a PHP instance.
 *
 * @since 0.1.0
 */
static PHP_MINIT_FUNCTION( mf2 )
{
#define X(str) \
	MF2_STR(str_ ## str) = zend_new_interned_string(zend_string_init(#str, sizeof(#str) - 1, 1));
	MF2_STR_DEFS
#undef X

	PHP_MINIT( mf2parse )( INIT_FUNC_ARGS_PASSTHRU );

	return SUCCESS;
}

/**
 * Shutdown the extension when it is unloaded by a PHP, at final shutdown.
 *
 * @since 0.1.0
 */
static PHP_MSHUTDOWN_FUNCTION( mf2 )
{
#define X(str) zend_string_release(MF2_STR(str_ ## str));
	MF2_STR_DEFS
#undef X

	return SUCCESS;
}

/**
 * A callback function triggered when phpinfo() is run.
 *
 * @since 0.1.0
 */
static PHP_MINFO_FUNCTION( mf2 )
{
	php_info_print_table_start();
	php_info_print_table_header( 2, "Microformats2 support", "enabled" );
	php_info_print_table_end();
}

ZEND_BEGIN_ARG_INFO_EX( arginfo_mf2_fetch, 0, 0, 1 )
	ZEND_ARG_TYPE_INFO( 0, uri, IS_STRING, 0 )
	ZEND_ARG_TYPE_INFO( 0, base_url, IS_STRING, 1 )
	ZEND_ARG_TYPE_INFO( 0, options, IS_LONG, 1 )
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX( arginfo_mf2_parse, 0, 0, 1 )
	ZEND_ARG_TYPE_INFO( 0, data, IS_STRING, 0 )
	ZEND_ARG_TYPE_INFO( 0, base_url, IS_STRING, 1 )
	ZEND_ARG_TYPE_INFO( 0, options, IS_LONG, 1 )
ZEND_END_ARG_INFO()

static const zend_function_entry php_mf2_functions[] = {
	PHP_FE(mf2_fetch, arginfo_mf2_fetch)
	PHP_FE(mf2_parse, arginfo_mf2_parse)
	PHP_FE_END
};

zend_module_entry php_mf2_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	php_mf2_deps,
	"mf2",
	php_mf2_functions,
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