<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 256 + 32 * 2, 192 + 32 * 2);
$context = new Context($surface);
$s = new Image(ImageFormat::ARGB32, 100, 100);
$s->createFromPng(dirname(__FILE__).'/romedalen.png');
$context->setSurface($s, 32, 32);
$pat = $context->getPattern();
$pat->setExtend(Extend::REPEAT);
$context->setPattern($pat);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/extend-repeat-php.png');
