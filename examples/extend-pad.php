<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 90, 90);
$context = new Context($surface);
$context->setSourceRgba(0, 0, 0, 1);
$context->rectangle(0, 0, 90, 90);
$context->fill();

$surfaceSize = (90 - 30) / 10;

$surface = new Image(ImageFormat::RGB24, $surfaceSize, $surfaceSize);
$con2 = new Context($surface);
$con2->setSourceRgb(1, 1, 1);
$con2->rectangle(0, 0, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(1, 0, 0);
$con2->rectangle($surfaceSize / 2, 0, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(0, 1, 0);
$con2->rectangle(0, $surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(0, 0, 1);
$con2->rectangle($surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();

$context->scale(10, 10);
$context->setSurface($surface, 1.5, 1.5);

/* Using EXTEND_REFLECT makes this test pass for image and xlib backends */
$pattern = $context->getPattern();
$pattern->setExtend(Extend::PAD);
$context->rectangle(1.5, 1.5, 6, 6);
$context->clip();
$context->setPattern($pattern);
$context->paint();
$surface->writeToPng(dirname(__FILE__).'/extend-pad-php.png');




