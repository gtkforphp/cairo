<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 8;
$height = 8;
$string = '';

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$s = new Image(ImageFormat::A8, $width, $height);
$stride = $s->getStride();

for ($i = 0; $i < 8; $i++)
{
	$string = $string.chr(0);
	$string = $string.chr(0);
	$string = $string.chr(255);
	$string = $string.chr(0);
	$string = $string.chr(255);
	$string = $string.chr(0);
	$string = $string.chr(0);
	$string = $string.chr(0);
}

echo $string;

$s->createForData($string, ImageFormat::A8, $width, $height);

$context->setSourceRgb(0, 0, 1);
$context->paint();
$context->setSourceRgb(1, 0, 0);
$context->maskSurface($s, 0, 0);

$surface->writeToPng(dirname(__FILE__).'/a8-mask-php.png');
