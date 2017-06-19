<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 12;
$height = 4;
$string = '';

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);

$s = new Image(ImageFormat::ARGB32, $width, $height);
$stride = $s->getStride();

for ($i = 0; $i < 12; $i++)
{
	$string = $string.chr(0x00); // blue
	$string = $string.chr(0x00); // green
	$string = $string.chr(0xff); // red
	$string = $string.chr(0xff); // alpha
	$string = $string.chr(0x00);
	$string = $string.chr(0xff);
	$string = $string.chr(0x00);
	$string = $string.chr(0xff);
	$string = $string.chr(0xff);
	$string = $string.chr(0x00);
	$string = $string.chr(0x00);
	$string = $string.chr(0xff);
	$string = $string.chr(0xff);
	$string = $string.chr(0xff);
	$string = $string.chr(0xff);
	$string = $string.chr(0xff);
}

$s->createForData($string, ImageFormat::ARGB32, $width, $height);
$context->setSourceRgb(1, 1, 1);
$context->paint();

$context->setSurface($s, 0, 0);
$context->paint();
$surface->writeToPng(dirname(__FILE__).'/bilevel-image-php.png');
