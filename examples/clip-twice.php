<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 64;
$height = 64;

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);
$context->newPath();
$context->arc($width / 2, $height / 2, $width / 3, 0, 2 * M_PI);
$context->clip();
$context->newPath();
$context->moveTo(0, 0);
$context->lineTo($width / 4, $height / 2);
$context->lineTo(0, $height);
$context->lineTo($width, $height);
$context->lineTo(3 * $width / 4, $height / 2);
$context->lineTo($width, 0);
$context->closePath();
$context->clip();
$context->setSourceRgb(0, 0, 0.6);
$context->newPath();
$context->moveTo(0, 0);
$context->lineTo(0, $height);
$context->lineTo($width / 2, 3 * $height / 4);
$context->lineTo($width, $height);
$context->lineTo($width, 0);
$context->lineTo($width / 2, $height / 4);
$context->closePath();
$context->fill();
$context->newPath();
$context->arc($width / 2, $height / 2, $width / 5, 0, 2 * M_PI);
$context->clip();
$context->setSourceRgb(1, 1, 0);
$context->paint();


$surface->writeToPng(dirname(__FILE__).'/clip-twice-php.png');

