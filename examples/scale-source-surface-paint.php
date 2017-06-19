<?php

use Cairo\Context;
use Cairo\Filter;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 12, 12);
$context = new Context($surface);

$data = '';

for ($i = 0; $i < 2; $i++)
{
	$data .= chr(0xff);
	$data .= chr(0xff);
	$data .= chr(0xff);
	$data .= chr(0xff);
	
	$data .= chr(0xff);
	$data .= chr(0xff);
	$data .= chr(0xff);
	$data .= chr(0xff);
	
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0xff);
	$data .= chr(0xff);
	
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0xff);
	$data .= chr(0xff);
}

for ($i = 0; $i < 2; $i++)
{
	$data .= chr(0x00);
	$data .= chr(0xff);
	$data .= chr(0x00);
	$data .= chr(0xff);
	
	$data .= chr(0x00);
	$data .= chr(0xff);
	$data .= chr(0x00);
	$data .= chr(0xff);
	
	$data .= chr(0xff);
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0xff);
	
	$data .= chr(0xff);
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0xff);
}

echo $data;

$s = new Image(ImageFormat::ARGB32, 100, 100);
$s->createForData($data, ImageFormat::RGB24, 4, 4, 16);
$context->scale(2, 2);
$context->setSurface($s, 1, 1);
$pat = $context->getPattern();
$pat->setFilter(Filter::NEAREST);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/scale-source-surface-paint-php.png');
