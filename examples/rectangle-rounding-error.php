<?php

use Cairo\Antialias;
use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 76, 76);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setAntialias(Antialias::NONE);
$context->setSourceRgb(0, 0, 0);

$context->translate(-300, -300);
$context->scale(677.0 / 26, 677.0 / 26);
$context->translate(1, 1);
$context->rectangle(11, 11, 1, 1);
$context->rectangle(11, 12, 1, 1);
$context->rectangle(12, 11, 1, 1);
$context->rectangle(12, 12, 1, 1);
$context->setSourceRgb(0, 0, 0);
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/rectangle-rounding-error-php.png');
