<?php

use Cairo\Context;
use Cairo\Operator;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 40;
$pad = 2;
$width = ($pad + $size + $pad);
$height = $width;

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$context->translate($pad, $pad);
$context->moveTo($size / 5, $size / 5);
$context->relLineTo($size / 2, 0);
$context->relLineTo($size / -2, $size / 2);
$context->closePath();

$context->setOperator(Operator::SOURCE);
$context->setSourceRgba(1, 0, 0, 0.5);

$context->fill();

$context->arc($size / 2, $size / 2, $size / 4, 0, 2 * M_PI);
$context->setOperator(Operator::OVER);
$context->setSourceRgba(0, 1, 0, 0.5);

$context->fill();

$context->moveTo($size / 2, $size / 2);
$context->relLineTo($size / 2, 0);
$context->relLineTo($size / -2, $size / 2);
$context->closePath();

$context->setOperator(Operator::SOURCE);
$context->setSourceRgba(1, 0, 0, 0.5);

$context->fill();

$surface->writeToPng(dirname(__FILE__).'/over-between-source-php.png');
