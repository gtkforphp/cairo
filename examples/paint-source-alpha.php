<?php

use Cairo\Context;
use Cairo\Filter;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 32, 32);
$context = new Context($surface);

$data = '';

for ($i = 0; $i < 2; $i++)
{
	$data .= chr(0x80);
	$data .= chr(0x80);
	$data .= chr(0x80);
	$data .= chr(0x80);
	
	$data .= chr(0x80);
	$data .= chr(0x80);
	$data .= chr(0x80);
	$data .= chr(0x80);
	
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0x80);
	$data .= chr(0x80);
	
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0x80);
	$data .= chr(0x80);
}

for ($i = 0; $i < 2; $i++)
{
	$data .= chr(0x00);
	$data .= chr(0x80);
	$data .= chr(0x00);
	$data .= chr(0x80);
	
	$data .= chr(0x00);
	$data .= chr(0x80);
	$data .= chr(0x00);
	$data .= chr(0x80);
	
	$data .= chr(0x80);
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0x80);
	
	$data .= chr(0x80);
	$data .= chr(0x00);
	$data .= chr(0x00);
	$data .= chr(0x80);
}

echo $data;

$s = new Image(ImageFormat::ARGB32, 100, 100);
$s->createForData($data, ImageFormat::ARGB32, 4, 4, 16);
$context->scale(4, 4);
$context->setSurface($s, 2, 2);
$pat = $context->getPattern();
$pat->setFilter(Filter::NEAREST);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/paint-source-alpha-php.png');
