dnl
dnl config.m4 for extension mf2
dnl

PHP_ARG_ENABLE(mf2, whether to enable mf2 support,
[  --enable-mf2            Enable microformats2 support])

if test "$PHP_MF2" != "no"; then

	AC_DEFINE(HAVE_MF2, 1, [Whether you have mf2])
	PHP_NEW_EXTENSION(mf2, php_mf2.c, $ext_shared)

fi