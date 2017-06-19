<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 50;
$height = 50;
$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$context->setSourceRgb(0.5, 0.5, 0.5);
$context->paint();
$context->save();
$pattern = new Linear(0, 0, 10.0, 0);
$pattern->addColorStopRgb(0.0, 0.0, 0.0, 1.0);
$pattern->addColorStopRgb(1.0, 1.0, 0.0, 0.0);
$pattern->setExtend(Extend::REFLECT);
$context->setPattern($pattern);
$context->rectangle(0.0, 0.0, $width, $height);
$context->fill();
$context->restore();

$surface->writeToPng(dirname(__FILE__).'/linear-gradient-reflect-php.png');
