<?php
$size = 40;

$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
$con = new CairoContext($sur);
$con->setSourceRgb(1, 1, 1);	/* White */
$con->paint();

$con->moveTo($size,    0);
$con->lineTo($size, $size);
$con->lineTo(0,    $size);

$con->setSourceRgb(0, 0, 0);
$con->fill();

/* Create a pattern with the target surface as the source,
 * offset by $size/2 */
$pattern = new CairoSurfacePattern ($sur);
$matrix = new CairoMatrix();
$matrix->translate(- $size / 2, - $size / 2);
$pattern->setMatrix($matrix);
$con->setSource ($pattern);

/* Copy two rectangles from the upper-left quarter of the image to
 * the lower right.  It will work if we use $con->fill(), but the
 * $con->clip() $con->paint() combination fails because the clip
 * on the surface as a destination affects it as the source as
 * well.
 */

$con->rectangle(
         2 * $size / 4, 2 * $size / 4,
         $size / 4,     $size / 4);
$con->rectangle(
         3 * $size / 4, 3 * $size / 4,
         $size / 4,     $size / 4);
$con->clip();
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . '/self-copy.png');