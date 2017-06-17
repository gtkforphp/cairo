<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 10, 20);
$context = new Context($surface);
$context->translate(1.0, 1.0);
$context->setSourceRgb(1, 0, 0); /* red */

/* First draw the desired shape with a fill */
$context->rectangle(0.5, 0.5, 4.0, 4.0);
$context->rectangle(3.5, 3.5, 4.0, 4.0);
$context->rectangle(3.5, 1.5, -2.0, 2.0);
$context->rectangle(6.5, 4.5, -2.0, 2.0);
$context->fill();

/* Then try the same thing with a stroke */
$context->translate(0, 10);
$context->moveTo(1.0, 1.0);
$context->relLineTo(3.0, 0.0);
$context->relLineTo(0.0, 6.0);
$context->relLineTo(3.0, 0.0);
$context->relLineTo(0.0, -3.0);
$context->relLineTo(-6.0, 0.0);
$context->closePath();

$context->setLineWidth(1.0);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/self-intersecting-php.png');
