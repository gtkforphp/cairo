<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 36, 36);
$context = new Context($surface);
$s = new Image(ImageFormat::ARGB32, 2, 2);
$con2 = new Context($s);
$con2->setSourceRgb(1, 0, 0);
$con2->paint();
$con2->setSourceRgb(0, 0, 1);
$con2->rectangle(0, 1, 1, 1);
$con2->rectangle(1, 0, 1, 1);
$con2->fill();

$context->setSourceRgb(0, 0, 0);
$context->paint();
$context->save();
$context->translate(3, 3);
$context->scale(10, 10);
$context->translate(0.5, 0.5);
$context->setSurface($s, 0, 0);
$context->paint();
$context->restore();

$surface->writeToPng(dirname(__FILE__).'/filter-bilinear-extents-php.png');
