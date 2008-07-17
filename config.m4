dnl
dnl $ Id: cairo 1.0.1$
dnl

PHP_ARG_ENABLE(cairo, whether to enable Cairo functions,
[  --with-cairo         Enable Cairo support])

if test "$PHP_CAIRO" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_CAIRO"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 50000
#error  this extension requires at least PHP version 5.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 5.0.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(CAIRO_SHARED_LIBADD)
  AC_DEFINE(HAVE_CAIRO, 1, [ ])

  PHP_NEW_EXTENSION(cairo, cairo.c , $ext_shared)

  AC_MSG_CHECKING(for pkg-config)
  if test ! -f "$PKG_CONFIG"; then
  	PKG_CONFIG=`which pkg-config`
  fi
  if test -f "$PKG_CONFIG"; then
  	AC_MSG_RESULT(found)
	AC_MSG_CHECKING(for cairo)

	if $PKG_CONFIG --exists cairo; then
	  AC_MSG_RESULT(found)
	  LDFLAGS="$LDFLAGS `$PKG_CONFIG --libs cairo`"
	  CFLAGS="$CFLAGS `$PKG_CONFIG --cflags cairo`"
	  AC_DEFINE(HAVE_CAIRO, 1, [whther cairo exists in the system])
	else
	  AC_MSG_RESULT(not found)
	  AC_MSG_ERROR(Ooops ! no cairo detected in the system)
	fi
  else
  	AC_MSG_RESULT(not found)
	AC_MSG_ERROR(Ooops ! no pkg-config found .... )
  fi
fi

