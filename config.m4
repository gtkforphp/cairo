dnl
dnl $ Id: cairo 1.0.1$
dnl

PHP_ARG_WITH(cairo, for Cairo graphics library support,
[  --with-cairo            Enable Cairo support], yes)

if test "$PHP_CAIRO" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_CAIRO"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 50200
#error  this extension requires at least PHP version 5.2.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 5.2.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"

  PHP_SUBST(CAIRO_SHARED_LIBADD)
  AC_DEFINE(HAVE_CAIRO, 1, [ ])

  PHP_NEW_EXTENSION(cairo, cairo.c cairo_error.c cairo_context.c cairo_pattern.c cairo_matrix.c cairo_path.c \
    cairo_surface.c cairo_image_surface.c cairo_svg_surface.c cairo_pdf_surface.c cairo_ps_surface.c \
    cairo_font.c cairo_font_options.c cairo_font_face.c cairo_scaled_font.c cairo_ft_font.c \
    cairo_recording_surface.c cairo_sub_surface.c, $ext_shared)

  EXT_CAIRO_HEADERS="php_cairo_api.h"

  ifdef([PHP_INSTALL_HEADERS], [
    PHP_INSTALL_HEADERS(ext/cairo, $EXT_CAIRO_HEADERS)
  ])

  if test "$PHP_CAIRO" != "no"; then
      CAIRO_CHECK_DIR=$PHP_CAIRO
      CAIRO_TEST_FILE=/include/cairo.h
      CAIRO_LIBNAME=cairo
  fi
  condition="$CAIRO_CHECK_DIR$CAIRO_TEST_FILE"

  if test -r $condition; then
   CAIRO_DIR=$CAIRO_CHECK_DIR
     CFLAGS="$CFLAGS -I$CAIRO_DIR/include"
   LDFLAGS=`$CAIRO_DIR/bin/cairo-config --libs`
  else
    AC_MSG_CHECKING(for pkg-config)
  
    if test ! -f "$PKG_CONFIG"; then
      PKG_CONFIG=`which pkg-config`
    fi

      if test -f "$PKG_CONFIG"; then
        AC_MSG_RESULT(found)
        AC_MSG_CHECKING(for cairo)
    
        if $PKG_CONFIG --exists cairo; then
            if $PKG_CONFIG --atleast-version=1.10 cairo; then
                cairo_version_full=`$PKG_CONFIG --modversion cairo`
                AC_MSG_RESULT([found $cairo_version_full])
                CAIRO_LIBS="$LDFLAGS `$PKG_CONFIG --libs cairo`"
                CAIRO_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I cairo`"
                PHP_EVAL_INCLINE($CAIRO_INCS)
                PHP_EVAL_LIBLINE($CAIRO_LIBS, CAIRO_SHARED_LIBADD)
                AC_DEFINE(HAVE_CAIRO, 1, [whether cairo exists in the system])

                AC_MSG_CHECKING(for Freetype)
                if $PKG_CONFIG --exists freetype2; then
                    freetype_version_full=`$PKG_CONFIG --modversion freetype2`
                    AC_MSG_RESULT([found $freetype_version_full])
                    FREETYPE_LIBS="$LDFLAGS `$PKG_CONFIG --libs freetype2`"
                    FREETYPE_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I freetype2`"
                    PHP_EVAL_INCLINE($FREETYPE_INCS)
                    PHP_EVAL_LIBLINE($FREETYPE_LIBS, FREETYPE_SHARED_LIBADD)
                    AC_DEFINE(HAVE_FREETYPE, 1, [whether freetype2 exists in the system])
                fi

                AC_MSG_CHECKING(for fontconfig)
                if $PKG_CONFIG --exists fontconfig; then
                    fontconfig_version_full=`$PKG_CONFIG --modversion fontconfig`
                    AC_MSG_RESULT([found $fontconfig_version_full])
                    FONTCONFIG_LIBS="$LDFLAGS `$PKG_CONFIG --libs fontconfig`"
                    FONTCONFIG_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I fontconfig`"
                    PHP_EVAL_INCLINE($FONTCONFIG_INCS)
                    PHP_EVAL_LIBLINE($FONTCONFIG_LIBS, FONTCONFIG_SHARED_LIBADD)
                    AC_DEFINE(HAVE_FONTCONFIG, 1, [whether fontconfig exists in the system])
                fi
                    
            else
                AC_MSG_RESULT(too old)
                AC_MSG_ERROR(Ooops ! You need at least cairo 1.10)
            fi
        else
            AC_MSG_RESULT(not found)
            AC_MSG_ERROR(Ooops ! no cairo detected in the system)
        fi
      else
        AC_MSG_RESULT(not found)
        AC_MSG_ERROR(Ooops ! no pkg-config found .... )
      fi
   fi
fi
