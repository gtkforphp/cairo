/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth Smith <auroraeosrose@php.net>                      |
  |         Michael Maclean <mgdm@php.net>                               |
  |         Akshat Gupta <g.akshat@gmail.com>                            |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cairo.h>

#ifdef CAIRO_HAS_FT_FONT
/*
cairo_font_face_t*  cairo_ft_font_face_create_for_ft_face
                                                        (FT_Face face,
                                                         int load_flags);
cairo_font_face_t*  cairo_ft_font_face_create_for_pattern
                                                        (FcPattern *pattern);
void                cairo_ft_font_options_substitute    (const cairo_font_options_t *options,
                                                         FcPattern *pattern);
FT_Face             cairo_ft_scaled_font_lock_face      (cairo_scaled_font_t *scaled_font);
void                cairo_ft_scaled_font_unlock_face    (cairo_scaled_font_t *scaled_font); */
#endif