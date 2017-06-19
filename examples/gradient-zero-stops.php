<?php

use Cairo\Context;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Pattern\Gradient\Radial;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 2, 2);
$context = new Context($surface);

$pat = new Linear(0, 0, 1, 1);
$context->setPattern($pat);
$context->paint();

unset($pat);

$pat = new Radial(0, 0, 0, 1, 1, 1);
$context->setPattern($pat);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/gradient-zero-stops-php.png');
