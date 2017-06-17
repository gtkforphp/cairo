<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 71;
$height = 28;
$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$dash = [8.0, 2.0];
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setSourceRgb(0., 0., 0);
$context->setLineWidth(2); /* This is vital to reproduce the bug. */

/* First check simple rectangles */
$context->rectangle(2, 2, 67, 24);
$context->setDash($dash, 9.0);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/leaky-dash-php.png');
