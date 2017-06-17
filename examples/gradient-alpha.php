<?php

use Cairo\Context;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 10, 10);
$context = new Context($surface);

$pat = new Linear(0, -10, 0, 10);
$pat->addColorStopRgba(0, 1, 0, 0, 1);
$pat->addColorStopRgba(1, 0, 0, 1, 0.5);
$context->setPattern($pat);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/gradient-alpha-php.png');
