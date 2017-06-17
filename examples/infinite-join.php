<?php

use Cairo\Context;
use Cairo\LineJoin;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 8, 8);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();

$context->setSourceRgb(0, 0, 0);
$context->setLineJoin(LineJoin::ROUND);
$context->scale(20.0 / 100.0, 20 / 100.);
$context->scale(1. / 20, 1. / 20);
$context->setLineWidth(20);
$context->translate(-18300, -13200);

$context->newPath();
$context->moveTo(18928, 13843);
$context->lineTo(18500, 13843);
$context->lineTo(18500, 13400);
$context->lineTo(18928, 13400);
$context->lineTo(18928, 13843);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/infinite-join-php.png');
