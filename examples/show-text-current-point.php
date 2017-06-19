<?php

use Cairo\Context;
use Cairo\FontSlant;
use Cairo\FontWeight;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 300, 16);
$context = new Context($surface);
$context->save();
$context->setSourceRgb(1, 1, 1); /* white */
$context->paint();
$context->restore();

$context->selectFontFace('Bitstream Vera Sans', FontSlant::NORMAL, FontWeight::NORMAL);
$context->setFontSize(12);
$context->setSourceRgb(0, 0, 0); /* black */

$context->moveTo(0, 12);
$context->showText('Hello from the ');
$context->showText('show-text-current-point-php');
$context->showText(' test.');

$surface->writeToPng(dirname(__FILE__).'/show-text-current-point-php.png');
