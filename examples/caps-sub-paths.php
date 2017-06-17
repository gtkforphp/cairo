<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 20, 20);
$context = new Context($surface);

$context->save();
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->restore();

$context->setLineWidth(4);
$context->setLineCap(LineCap::ROUND);
$context->moveTo(4, 4);
$context->lineTo(4, 16);
$context->moveTo(10, 4);
$context->lineTo(10, 16);
$context->moveTo(16, 4);
$context->lineTo(16, 16);

$context->stroke();
$surface->writeToPng(dirname(__FILE__).'/caps-sub-paths-php.png');

