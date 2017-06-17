<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 10;
$pad = 2;
$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);

$context->setSourceRgb(0, 0, 1);
$context->rectangle($pad, $pad, $size - 2 * $pad, $size - 2 * $pad);
$context->fill();

$s = $context->getGroupSurface();
$c = $s->getContent();
$s1 = $s->createSimilar($c, $size / 2, $size / 2);

$s1->setDeviceOffset($size / -2, $size / -2);

$c = new Context($s1);
$c->setSourceRgb(1, 0, 0);
$c->rectangle($pad, $pad, $size - 2 * $pad, $size - 2 * $pad);
$c->fill();

$context->setSurface($s1, 0, 0);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/device-offset-php.png');
