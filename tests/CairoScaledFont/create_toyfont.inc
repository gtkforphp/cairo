<?php
if(function_exists('cairo_toy_font_face_create')) {
    $fontface = new CairoToyFontFace('sans-serif');
} else {
    $surface = new Cairo\Surface\Image(CAIRO_FORMAT_ARGB32, 50, 50);
    $context = new CairoContext($surface);
    $context->selectFontFace('sans-serif');
    $fontface = $context->getFontFace();
    unset($surface, $context);
}