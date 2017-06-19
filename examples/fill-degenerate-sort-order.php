<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 190, 120);
$context = new Context($surface);

$context->setSourceRgb(1, 0, 0);
$context->moveTo(43, 103);
$context->lineTo(91, 101);
$context->lineTo(0, 112);
$context->lineTo(60, 0);
$context->lineTo(91, 101);
$context->lineTo(43, 103);
$context->lineTo(176, 110);
$context->lineTo(116, 100);
$context->lineTo(176, 0);
$context->lineTo(176, 110);
$context->closePath();
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/fill-degenerate-sort-order-php.png');
