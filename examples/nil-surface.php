<?php

use Cairo\Context;
use Cairo\Pattern\Surface as PatternSurface;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 1, 1);
$context = new Context($surface);

$con2 = new Context($surface);
$s = new Image(ImageFormat::ARGB32, 0, 0);
$s->createFromPng('__THIS_FILE_DOES_NOT_EXIST');

$patternSurface = new PatternSurface($s);
$con2->setPattern($patternSurface);
$con2->paint();

$con2 = $context->getSurface();
$patternSurface = new PatternSurface(null);
$con2->setPattern($patternSurface);
$con2->paint();

$surface->writeToPng(dirname(__FILE__).'/nil-surface-php.png');
