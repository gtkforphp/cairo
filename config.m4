dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(cairo, This extension requires the Cairo Vector Graphics Library version 1.2.2 
   or above and a working pkg-config installation.,[  --with-cairo[=DIR]   With cairo support])


if test "$PHP_CAIRO" != "no"; then

  
  if test -z "$PKG_CONFIG"
  then
	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  fi
  if test "$PKG_CONFIG" = "no"
  then
	AC_MSG_ERROR([required utility 'pkg-config' not found])
  fi

  if ! $PKG_CONFIG --exists cairo
  then
	AC_MSG_ERROR(['cairo' not known to pkg-config])
  fi

  if ! $PKG_CONFIG --atleast-version 1.2.2 cairo
  then
	PKG_VERSION=`$PKG_CONFIG --modversion cairo`
	AC_MSG_ERROR(['cairo'\ is version $PKG_VERSION, 1.2.2 required])
  fi

  PHP_EVAL_INCLINE(`$PKG_CONFIG --cflags-only-I cairo`)
  PHP_EVAL_LIBLINE(`$PKG_CONFIG --libs cairo`, CAIRO_SHARED_LIBADD)

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_CAIRO"
  AC_CHECK_HEADER([cairo.h], [], AC_MSG_ERROR('cairo.h' header not found))
  export CPPFLAGS="$OLD_CPPFLAGS"

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_CAIRO"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 40000
#error  this extension requires at least PHP version 4.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 4.0.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(CAIRO_SHARED_LIBADD)
  AC_DEFINE(HAVE_CAIRO, 1, [ ])
  AC_DEFINE([_CAIROINT_H_], [1], [do not include BC definitions])

  PHP_NEW_EXTENSION(cairo, cairo.c , $ext_shared)

fi

