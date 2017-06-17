<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 25;
$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);
/* Paint background white, then draw in black. */
$context->setSourceRgb(1.0, 1.0, 1.0); /* white */
$context->paint();
$context->setSourceRgb(0.0, 0.0, 0.0); /* black */
$context->setLineWidth(1.0);
$context->translate(1, 1);

/* Draw everything first with square caps. */
$context->setLineCap(LineCap::SQUARE);

/* Draw horizontal and vertical segments, each in both
 * directions. */
$context->moveTo(4.5, 0.5);
$context->relLineTo(2.0, 0.0);

$context->moveTo(10.5, 4.5);
$context->relLineTo(0.0, 2.0);

$context->moveTo(6.5, 10.5);
$context->relLineTo(-2.0, 0.0);

$context->moveTo(0.5, 6.5);
$context->relLineTo(0.0, -2.0);

/* Draw right angle turns in four directions. */
$context->moveTo(0.5, 2.5);
$context->relLineTo(0.0, -2.0);
$context->relLineTo(2.0, 0.0);

$context->moveTo(8.5, 0.5);
$context->relLineTo(2.0, 0.0);
$context->relLineTo(0.0, 2.0);

$context->moveTo(10.5, 8.5);
$context->relLineTo(0.0, 2.0);
$context->relLineTo(-2.0, 0.0);

$context->moveTo(2.5, 10.5);
$context->relLineTo(-2.0, 0.0);
$context->relLineTo(0.0, -2.0);

/* Draw a closed-path rectangle */
$context->rectangle(0.5, 12.5, 10.0, 10.0);

$context->stroke();

$context->translate(12, 0);

/* Now draw the same results, but with butt caps. */
$context->setLineCap(LineCap::BUTT);

/* Draw horizontal and vertical segments, each in both
 * directions. */
$context->moveTo(4.0, 0.5);
$context->relLineTo(3.0, 0.0);

$context->moveTo(10.5, 4.0);
$context->relLineTo(0.0, 3.0);

$context->moveTo(7.0, 10.5);
$context->relLineTo(-3.0, 0.0);

$context->moveTo(0.5, 7.0);
$context->relLineTo(0.0, -3.0);

/* Draw right angle turns in four directions. */
$context->moveTo(0.5, 3.0);
$context->relLineTo(0.0, -2.5);
$context->relLineTo(2.5, 0.0);

$context->moveTo(8.0, 0.5);
$context->relLineTo(2.5, 0.0);
$context->relLineTo(0.0, 2.5);

$context->moveTo(10.5, 8.0);
$context->relLineTo(0.0, 2.5);
$context->relLineTo(-2.5, 0.0);

$context->moveTo(3.0, 10.5);
$context->relLineTo(-2.5, 0.0);
$context->relLineTo(0.0, -2.5);

/* Draw a closed-path rectangle */
$context->rectangle(0.5, 12.5, 10.0, 10.0);

/* Draw a path that is rectilinear initially, but not completely */
/* We draw this out of the target window.  The bug that caused this
 * addition was leaks if part of the path was rectilinear but not
 * completely */
$context->moveTo(3.0, 30.5);
$context->relLineTo(-2.5, 0.0);
$context->relLineTo(+2.5, +2.5);

$context->stroke();
$surface->writeToPng(dirname(__FILE__).'/rectilinear-stroke-php.png');
