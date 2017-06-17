<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;


$char = 'Cairo';
$surface = new Image(0, 500, 500);
$context = new Context($surface);

$context->selectFontFace('Sans');
$context->setFontSize(100);
$ext = $context->getTextExtents($char);

$x = 25.0;
$y = 150.0;
$context->moveTo($x, $y);
$context->showText($char);

$context->setSourceRgba(1, 0.2, 0.2, 0.6);
$context->setLineWidth(6.0);
$context->arc($x, $y, 10, 0, 2 * 3.14);
$context->fill();
$context->moveTo($x, $y);
$context->relLineTo(0, -1 * $ext['height']);
$context->relLineTo($ext['width'], 0);
$context->relLineTo($ext['x_bearing'], -1 * $ext['y_bearing']);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/text-extents-php.png');
