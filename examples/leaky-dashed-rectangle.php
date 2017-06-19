<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 60;
$height = 60;
$dash = [4.0, 2.0];

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setSourceRgb(0., 0., 0);
$context->translate(0.5, .5);
$context->setLineWidth(1); /* This is vital to reproduce the bug. */

/* First check simple rectangles */
$context->setSourceRgb(0., 0., 0);
$context->rectangle(-$width / 4, -$height / 4, $width, $height);
$context->stroke();
$context->rectangle($width + $width / 4, -$height / 4, -$width, $height);
$context->stroke();
$context->rectangle(-$width / 4, $height + $height / 4, $width, -$height);
$context->stroke();
$context->rectangle($width + $width / 4, $height + $height / 4, -$width, -$height);
$context->stroke();

$context->setDash($dash, 0);

/* And now dashed. */
$context->setSourceRgb(1., 0., 0);
$context->rectangle(-$width / 4, -$height / 4, $width, $height);
$context->stroke();
$context->setSourceRgb(0., 1., 0);
$context->rectangle($width + $width / 4, -$height / 4, -$width, $height);
$context->stroke();
$context->setSourceRgb(0., 0., 1);
$context->rectangle(-$width / 4, $height + $height / 4, $width, -$height);
$context->stroke();
$context->setSourceRgb(1., 1., 0);
$context->rectangle($width + $width / 4, $height + $height / 4, -$width, -$height);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/leaky-dashed-rectangle-php.png');
