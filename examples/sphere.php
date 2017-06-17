<?php

use Cairo\Context;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Pattern\Gradient\Radial;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(0, 256, 256);
$ctx = new Context($surface);
$ctx->setAntialias(0);
$ctx->setFillRule(0);
$ctx->scale(256 / 1.0, 256 / 1.0);

$pat = new Linear(0.0, 0.0, 0.0, 1.0);
$pat->addColorStopRgba(1, 0, 0, 0, 1);
$pat->addColorStopRgba(0, 1, 1, 1, 1);
$ctx->rectangle(0, 0, 1, 1);
$ctx->setPattern($pat);
$ctx->fill();

$pat = new Radial(0.45, 0.4, 0.1, 0.4, 0.4, 0.5);
$pat->addColorStopRgba(0, 1, 1, 1, 1);
$pat->addColorStopRgba(1, 0, 0, 0, 1);
$ctx->setPattern($pat);
$ctx->arc(.5, .5, .3, 0, 2 * 3.14);
$ctx->fill();

$check = $ctx->getSurface();

$check->writeToPng(dirname(__FILE__).'/sphere-php.png');
