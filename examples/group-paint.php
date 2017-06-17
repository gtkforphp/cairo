<?php

use Cairo\Context;
use Cairo\Operator;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 10, 10);
$context = new Context($surface);

$context->pushGroup();
$context->setSourceRgb(0, 0, 1);
$context->paint();

$context->popGroupToSource();
$context->setOperator(Operator::SOURCE);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/group-paint-php.png');
