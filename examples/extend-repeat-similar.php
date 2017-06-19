<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Operator;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 256 + 32 * 2, 192 + 32 * 2);
$context = new Context($surface);
$s = new Image(ImageFormat::ARGB32, 100, 100);
$s->createFromPng(dirname(__FILE__).'/romedalen.png');
$s1 = $surface->createSimilar($surface->getContent(), 320, 256);
$con2 = new Context($s1);
$con2->setSurface($s, 32, 32);
$con2->setOperator(Operator::SOURCE);
$pat = $con2->getPattern();
$pat->setExtend(Extend::REPEAT);
$con2->paint();
$context->setSurface($s1, 0, 0);
$context->paint();
$surface->writeToPng(dirname(__FILE__).'/extend-repeat-similar-php.png');
