<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 800;
$height = 800;

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->selectFontFace('Bitstream Vera Sans');
$context->setFontSize(10000);
$context->setSourceRgb(0, 0, 0);
$context->moveTo(-5000, 5000);
$context->showText('xW');

$surface->writeToPng(dirname(__FILE__).'/large-font-php.png');
