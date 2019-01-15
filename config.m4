dnl
dnl config.m4 for extension mf2
dnl

PHP_ARG_ENABLE(mf2, whether to enable mf2 support,
[  --enable-mf2            Enable microformats2 support])

if test -z "$PHP_LIBXML_DIR"; then
	PHP_ARG_WITH(libxml-dir, libxml2 install dir,
	[  --with-libxml-dir=DIR   MF2: libxml2 install prefix], no, no)
fi

if test "$PHP_MF2" != "no"; then

	if test "$PHP_LIBXML" = "no"; then
		AC_MSG_ERROR([mf2 extension requires LIBXML extension, add --enable-libxml])
	fi

	PHP_SETUP_LIBXML(MF2_SHARED_LIBADD, [
		AC_DEFINE(HAVE_MF2, 1, [Whether you have mf2])
		PHP_NEW_EXTENSION(mf2, mf2.c php_mf2.c user_mf2.c mf2parse.c php_mf2parse.c user_mf2parse.c mf2microformat.c php_mf2microformat.c, $ext_shared)
		PHP_SUBST(MF2_SHARED_LIBADD)
		PHP_ADD_EXTENSION_DEP(mf2, libxml)
	], [
		AC_MSG_ERROR([xml2-config not found. Please check your libxml2 installation.])
	])

fi