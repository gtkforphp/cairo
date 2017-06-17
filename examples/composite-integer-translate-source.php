<?php

use Cairo\Context;
use Cairo\Operator;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 100, 100);
$context = new Context($surface);

$s = new Image(ImageFormat::ARGB32, 1, 1);
$s->createFromPng(dirname(__FILE__).'/romedalen.png');

$context->setSourceRgb(0, 0, 0);
$context->rectangle(0, 0, 100, 100);
$context->fill();

$context->translate(10, 10);
$context->setOperator(Operator::SOURCE);
$context->setSurface($s, 0, 0);
$context->rectangle(0, 0, 90, 90);
$context->fill();
$surface->writeToPng(dirname(__FILE__).'/composite-integer-translate-source-php.png');
