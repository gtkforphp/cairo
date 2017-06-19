<?php

use Cairo\Context;
use Cairo\Surface\Pdf;

function drawPattern($surface, $size)
{
	$context = new Context($surface);
	$context->setSourceRgb(1, 1, 1);
	$context->rectangle(0, 0, $size / 2, $size / 2);
	$context->fill();
	$context->setSourceRgb(1, 0, 0);
	$context->rectangle($size / 2, 0, $size / 2, $size / 2);
	$context->fill();
	$context->setSourceRgb(0, 1, 0);
	$context->rectangle(0, $size / 2, $size / 2, $size / 2);
	$context->fill();
	$context->setSourceRgb(0, 0, 1);
	$context->rectangle($size / 2, $size / 2, $size / 2, $size / 2);
	$context->fill();
}

$size = 90;
$surface = new Pdf('pdf-surface-source.pdf', $size, $size);
$surface->setFallbackResolution(72, 72);
$context = new Context($surface);
$context->setSourceRgb(0, 0, 0);
$context->paint();

$surfaceSize = $size - 30;
$s = new Pdf('temp.pdf', $surfaceSize, $surfaceSize);
drawPattern($s, $surfaceSize);
$s->writeToPng(dirname(__FILE__).'/temp.png');
$context->setSurface($s, 15.0, 15.0);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/pdf-surface-source-php.png');
