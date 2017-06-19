<?php

use Cairo\Context;
use Cairo\FontSlant;
use Cairo\FontWeight;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 10, 10);
$context = new Context($surface);
$context->rectangle(0, 0, 10, 10);
$context->setSourceRgb(0, 0, 1);
$context->fill();

$context->resetClip();
$context->rectangle(2, 2, 2, 2);
$context->clip();
$context->rectangle(6, 6, 2, 2);
$context->clip();

$context->translate(0.5, 0.5);

$context->resetClip();
$context->rectangle(2, 2, 2, 2);
$context->clip();
$context->rectangle(6, 6, 6, 6);
$context->clip();

$context->rectangle(0, 0, 10, 10);
$context->setSourceRgb(1, 1, 0);
$context->fill();
$context->selectFontFace('Bitstream Vera Sans', FontSlant::NORMAL, FontWeight::NORMAL);
$context->moveTo(0, 10);
$context->showText('cairo');
$surface->writeToPng(dirname(__FILE__).'/clip-all-php.png');
