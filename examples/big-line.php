<?php

use Cairo\Context;
use Cairo\Surface\Ps;

$width = 100;
$height = 100;

$surface = new Ps('temp.ps', $width, $height);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 0);
$context->moveTo(50, 50);
$context->lineTo(50000, 50000);
$context->stroke();

$context->setSourceRgb(1, 0, 0);
$context->moveTo(50, 50);
$context->lineTo(-50000, 50000);
$context->stroke();

$context->setSourceRgb(0, 1, 0);
$context->moveTo(50, 50);
$context->lineTo(50000, -50000);
$context->stroke();

$context->setSourceRgb(0, 0, 1);
$context->moveTo(50, 50);
$context->lineTo(-50000, -50000);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/big-line-php.png');

