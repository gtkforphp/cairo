<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 28, 14);
$context = new Context($surface);
$context->rectangle(2, 2, 10, 10);
$context->setSourceRgb(0, 0, 1);
$context->fillPreserve();
$context->setSourceRgb(1, 0, 0);
$context->stroke();

$context->translate(14, 0);
$context->arc(7, 7, 5, 0, 2 * M_PI);
$context->fillPreserve();
$context->setSourceRgb(0, 0, 1);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/fill-and-stroke-php.png');


