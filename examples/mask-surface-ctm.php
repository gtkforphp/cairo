<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$data = '';

$surface = new Image(ImageFormat::ARGB32, 10, 10);
$context = new Context($surface);

for ($i = 0; $i < 4; $i++)
{
	$data = $data.chr(0x80);
	$data = $data.chr(0x00);
	$data = $data.chr(0x00);
	$data = $data.chr(0x00);
}

$s = new Image(ImageFormat::ARGB32, 1, 1);
$s->createForData($data, ImageFormat::ARGB32, 2, 2, 8);

$context->setSourceRgb(1, 0, 0);
$context->save();
$context->translate(2, 2);
$context->maskSurface($s, 0, 0);
$context->restore();
$context->maskSurface($s, 4, 4);
$context->translate(2, 2);
$context->maskSurface($s, 4, 4);

$surface->writeToPng(dirname(__FILE__).'/mask-surface-ctm-php.png');
