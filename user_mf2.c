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

#include <libxml/HTMLparser.h>

#include "zend_exceptions.h"

#include "mf2parse.h"
#include "php_mf2parse.h"

/**
 * @since 0.1.0
 */
PHP_FUNCTION(mf2_fetch)
{
	char *uri, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t uri_length, base_url_length;
	zend_long options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	zend_bool options_is_null = 0;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "URI parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 3 )
		Z_PARAM_STRING_EX( uri, uri_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
		Z_PARAM_LONG_EX( options, options_is_null, 1, 0 )
	ZEND_PARSE_PARAMETERS_END();

	if ( ZEND_SIZE_T_INT_OVFL( uri_length ) ) {
		zend_throw_exception( zend_ce_exception, "URI is too long", 0 );
		return;
	}

	if ( base_url != NULL ) {
		if ( ZEND_SIZE_T_INT_OVFL( base_url_length ) ) {
			zend_throw_exception( zend_ce_exception, "Base URL is too long", 0 );
			return;
		}
	}

	if ( ZEND_LONG_EXCEEDS_INT( options ) ) {
		zend_throw_exception( zend_ce_exception, "Invalid options", 0 );
		return;
	}

	object_init_ex(return_value, php_mf2parse_ce);

	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( return_value );

	if ( base_url != NULL ) {
		mf2parse->php_base_url = php_url_parse_ex( base_url, base_url_length );
		if ( mf2parse->php_base_url == NULL ) {
			zend_throw_exception( zend_ce_exception, "Invalid base URL", 0 );
			return;
		}
		if ( mf2parse->php_base_url->scheme == NULL ) {
			zend_throw_exception( zend_ce_exception, "Base URL must be absolute", 0 );
			return;
		}
		ZVAL_STRINGL( &mf2parse->base_url, base_url, base_url_length );
	}

	if ( options_is_null == 1 ) {
		mf2parse->options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	} else {
		mf2parse->options = options;
	}

	mf2parse_new_from_uri( return_value, uri, uri_length );
}

/**
 * @since 0.1.0
 */
PHP_FUNCTION(mf2_parse)
{
	char *data, *base_url = NULL;
	int num_args = ZEND_NUM_ARGS();
	size_t data_length, base_url_length;
	zend_long options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	zend_bool options_is_null = 0;

	if ( num_args == 0 ) {
		zend_throw_exception( zend_ce_exception, "Data parameter is required", 0 );
		return;
	}

	ZEND_PARSE_PARAMETERS_START( 1, 3 )
		Z_PARAM_STRING_EX( data, data_length, 0, 0 )
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING_EX( base_url, base_url_length, 1, 0 )
		Z_PARAM_LONG_EX( options, options_is_null, 1, 0 )
	ZEND_PARSE_PARAMETERS_END();

	if ( ZEND_SIZE_T_INT_OVFL( data_length ) ) {
		zend_throw_exception( zend_ce_exception, "Data is too long", 0 );
		return;
	}

	if ( base_url != NULL ) {
		if ( ZEND_SIZE_T_INT_OVFL( base_url_length ) ) {
			zend_throw_exception( zend_ce_exception, "Base URL is too long", 0 );
			return;
		}
	}

	if ( ZEND_LONG_EXCEEDS_INT( options ) ) {
		zend_throw_exception( zend_ce_exception, "Invalid options", 0 );
		return;
	}

	object_init_ex(return_value, php_mf2parse_ce);

	php_mf2parse_object *mf2parse = Z_MF2PARSEOBJ_P( return_value );

	if ( base_url != NULL ) {
		mf2parse->php_base_url = php_url_parse_ex( base_url, base_url_length );
		if ( mf2parse->php_base_url == NULL ) {
			zend_throw_exception( zend_ce_exception, "Invalid base URL", 0 );
			return;
		}
		if ( mf2parse->php_base_url->scheme == NULL ) {
			zend_throw_exception( zend_ce_exception, "Base URL must be absolute", 0 );
			return;
		}
		ZVAL_STRINGL( &mf2parse->base_url, base_url, base_url_length );
	}

	if ( options_is_null == 1 ) {
		mf2parse->options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
	} else {
		mf2parse->options = options;
	}

	mf2parse_new_from_data( return_value, data, data_length );
}

#endif /* HAVE_MF2 */