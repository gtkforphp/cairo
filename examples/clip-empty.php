<?php

use Cairo\Context;
use Cairo\FontSlant;
use Cairo\FontWeight;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 10, 10);
$context = new Context($surface);
$context->setSourceRgb(0, 0, 1);
$context->paint();

$context->resetClip();
$context->clip();

$context->translate(0.5, 0.5);

$context->setSourceRgb(0, 1, 0);
$context->rectangle(0, 0, 10, 10);
$context->fillPreserve();
$context->setSourceRgb(1, 0, 0);
$context->stroke();
$context->selectFontFace('Bitstream Vera Sans', FontSlant::NORMAL, FontWeight::NORMAL);
$context->moveTo(0, 10);
$context->showText('cairo');
$surface->writeToPng(dirname(__FILE__).'/clip-empty-php.png');

