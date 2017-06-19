<?php

use Cairo\Context;
use Cairo\Matrix;
use Cairo\Pattern\Surface as PatternSurface;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 40;

$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);
$context->setSourceRgb(1, 1, 1);    /* White */
$context->paint();

$context->moveTo($size, 0);
$context->lineTo($size, $size);
$context->lineTo(0, $size);

$context->setSourceRgb(0, 0, 0);
$context->fill();

/* Create a pattern with the target surface as the source,
 * offset by $size/2 */
$pattern = new PatternSurface($surface);
$matrix = new Matrix();
$matrix->translate(-$size / 2, -$size / 2);
$pattern->setMatrix($matrix);
$context->setPattern($pattern);

/* Copy two rectangles from the upper-left quarter of the image to
 * the lower right.  It will work if we use $context->fill(), but the
 * $context->clip() $context->paint() combination fails because the clip
 * on the surface as a destination affects it as the source as
 * well.
 */

$context->rectangle(2 * $size / 4, 2 * $size / 4, $size / 4, $size / 4);
$context->rectangle(3 * $size / 4, 3 * $size / 4, $size / 4, $size / 4);
$context->clip();
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/self-copy-php.png');