<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 53, 53);
$context = new Context($surface);

$context->setSourceRgb(1, 0, 0);
$context->translate(1,1);
$context->moveTo(0,0);
$context->lineTo(25,50);
$context->lineTo(25,0);
$context->lineTo(50,25);
$context->lineTo(0,25);
$context->closePath();
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/fill-missed-stop-php.png');
