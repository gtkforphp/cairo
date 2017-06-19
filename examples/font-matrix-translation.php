<?php

use Cairo\Context;
use Cairo\Matrix;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function boxText($context, $string, $x, $y)
{
	$context->save();
	$ext = $context->getTextExtents($string);
	$lw = $context->getLineWidth();
	$context->rectangle($x + $ext['x_bearing'] - $lw / 2, $y + $ext['y_bearing'] - $lw / 2, $ext['width'] + $lw, $ext['height'] + $lw);
	$context->stroke();
	$context->moveTo($x, $y);
	$context->showText($string);
	$context->restore();
}

$surface = new Image(ImageFormat::ARGB32, 38, 34);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->selectFontFace('Bitstream Vera Sans');
$context->setFontSize(12);
$context->translate(4, 4);
$context->setLineWidth(1);
$context->setSourceRgb(0, 0, 0);

$ext = $context->getTextExtents('text');

boxText($context, 'text', 0, -$ext['y_bearing']);

$matrix = new Matrix();
$matrix->translate(6, 16);
$matrix->scale(12, 12);
$context->setFontMatrix($matrix);
$context->setSourceRgb(0, 0, 1);

boxText($context, 'text', 0, -$ext['y_bearing']);

$surface->writeToPng(dirname(__FILE__).'/font-matrix-translation-php.png');
