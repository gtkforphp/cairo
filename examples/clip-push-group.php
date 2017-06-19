<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 10;
$pad = 2;

$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);

$context->setSourceRgb(1, 0, 0);
$context->paint();

$context->arc($size / 2, $size / 2, $size / 2 - $pad, 0, 2 * M_PI);
$context->clip();
$context->pushGroup();
$context->setSourceRgb(0, 0, 1);
$context->paint();
$context->popGroupToSource();
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/clip-push-group-php.png');

