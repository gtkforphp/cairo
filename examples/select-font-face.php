<?php

use Cairo\Context;
use Cairo\FontSlant;
use Cairo\FontWeight;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;


$textSize = 12;
$surface = new Image(ImageFormat::ARGB32, 192, 16);
$context = new Context($surface);

$context->save();
$context->setSourceRgb(1, 1, 1); /* white */
$context->paint();
$context->restore();

$context->setSourceRgb(0, 0, 0); /* black */
$context->selectFontFace('Bitstream Vera Serif', FontSlant::NORMAL, FontWeight::NORMAL);
$context->setFontSize($textSize);

$context->moveTo(0, $textSize);
$context->showText('i-am-serif');

$context->selectFontFace('Bitstream Vera Sans', FontSlant::NORMAL, FontWeight::NORMAL);
$context->showText(' i-am-sans');

$context->selectFontFace('Bitstream Vera Sans Mono', FontSlant::NORMAL, FontWeight::NORMAL);
$context->showText(' i-am-mono');

$surface->writeToPng(dirname(__FILE__).'/select-font-face-php.png');
