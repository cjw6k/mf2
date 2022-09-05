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

#include "zend_smart_str.h"
#include "ext/standard/php_string.h"
#include "ext/standard/url.h"

#include "mf2.h"

mf2_str_globals str_globals_mf2;

/**
 * Checks for the presence of a value inside an array.
 *
 * This code borrows very much from the standard PHP implementation in array.c.
 *
 * @see ext/standard/array.c
 *
 * @since 0.1.0
 *
 * @param  zval * haystack  The array of values to search within.
 * @param  zval * needle    The value for which to search the array.
 *
 * @return  zend_bool  0 If needle is in haystack.
 *                     1 If needle is not in haystack.
 */
zend_bool mf2_in_array( zval *haystack, zval *needle )
{
	zval *entry;

	ZVAL_DEREF( needle );

	if ( Z_TYPE_P( needle ) == IS_LONG ) {

		ZEND_HASH_FOREACH_VAL( Z_ARRVAL_P( haystack ), entry ) {
			if ( fast_equal_check_long ( needle, entry ) ) {
				return 1;
			}
		} ZEND_HASH_FOREACH_END();

	} else if ( Z_TYPE_P( needle ) == IS_STRING ) {

		ZEND_HASH_FOREACH_VAL( Z_ARRVAL_P( haystack ), entry ) {
			if ( fast_equal_check_string ( needle, entry ) ) {
				return 1;
			}
		} ZEND_HASH_FOREACH_END();

	} else {

		ZEND_HASH_FOREACH_VAL( Z_ARRVAL_P( haystack ), entry ) {
			if ( fast_equal_check_function( needle, entry ) ) {
				return 1;
			}
		} ZEND_HASH_FOREACH_END();

	}

	return 0;
}

/**
 * Checks for the presence of a zend_string value inside an array.
 *
 * @see mf2_in_array
 *
 * @since 0.1.0
 *
 * @param  zval * haystack       The array of values to search within.
 * @param  zend_string * needle  The value for which to search the array.
 *
 * @return  zend_bool  0 If needle is in haystack.
 *                     1 If needle is not in haystack.
 */
zend_bool mf2_string_in_array( zval *haystack, zend_string *needle )
{
	zval zv_needle;
	ZVAL_STRING( &zv_needle, ZSTR_VAL( needle ) );

	zend_bool result;
	result = mf2_in_array( haystack, &zv_needle );

	zval_dtor( &zv_needle );

	return result;
}

#if PHP_VERSION_ID < 80000
/**
 * Case insensitive string comparison for hash buckets.
 *
 * This callback is used by the zend_hash_sort function to sort values stored
 * within HashTables into alphabetical order. It relies on the non-portable
 * strcasecmp function.
 *
 * @since 0.1.0
 *
 * @param  const void * ida  A pointer to a hash bucket.
 * @param  const void * idb  A pointer to a hash bucket.
 *
 * @return  int  Indicating which string is earlier in the order.
 */
int mf2_strcasecmp( const void *ida, const void *idb )
{
    Bucket *first = ( Bucket * ) ida;
    Bucket *second = ( Bucket * ) idb;

    return strcasecmp( Z_STRVAL( first->val ), Z_STRVAL( second->val ) );
}
#else
/**
 * Case insensitive string comparison for hash buckets.
 *
 * This callback is used by the zend_hash_sort function to sort values stored
 * within HashTables into alphabetical order. It relies on the non-portable
 * strcasecmp function.
 *
 * @since 0.1.0
 *
 * @param  const struct _Bucket * first   A pointer to a bucket.
 * @param  const struct _Bucket * second  A pointer to a bucket.
 *
 * @return  int  Indicating which string is earlier in the order.
 */
int mf2_strcasecmp( struct _Bucket *first, struct _Bucket *second )
{
	return strcasecmp( Z_STRVAL( first->val ), Z_STRVAL( second->val ) );
}
#endif

/**
 * Remove white space from the beginning and end of a c-string.
 *
 * The HTML5 specification defines space characters:
 *
 *   "The space characters, for the purposes of this specification,
 *    are U+0020 SPACE, U+0009 CHARACTER TABULATION (tab),
 *    U+000A LINE FEED (LF), U+000C FORM FEED (FF), and
 *    U+000D CARRIAGE RETURN (CR)."
 *
 * @link https://www.w3.org/TR/html52/infrastructure.html#common-parser-idioms
 *
 * @since 0.1.0
 *
 * @param  zval * trimmed_string  The resultant trimmed string.
 * @param  char * string          The string to trim.
 */
void mf2_trim_html_space_chars( zval *trimmed_string, char *string )
{
	smart_str smart_data_str = {0};

	smart_str_appends( &smart_data_str, string );
	smart_str_0( &smart_data_str );

	zval_dtor( trimmed_string );
	ZVAL_STR( trimmed_string, php_trim( smart_data_str.s, " \t\r\f\n", 5, 3 ) );

	smart_str_free( &smart_data_str );
}

/**
 * Check if a given URL is a relative URL.
 *
 * @since 0.1.0
 *
 * @param  php_url * url_parts  The parsed URL.
 *
 * @return  zend_bool  0 The URL is not relative (it is absolute).
 *                     1 The URL is relative.
 */
zend_bool mf2_is_relative_url( php_url *url_parts )
{
	return NULL == url_parts->scheme ? 1 : 0;
}

#endif /* HAVE_MF2 */