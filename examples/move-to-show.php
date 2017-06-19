<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::RGB24, 2, 2);
$context = new Context($surface);
$s = new Image(ImageFormat::RGB24, 2, 2);

$c = [];

$color = '';
$color .= chr(0xff);
$color .= chr(0xff);
$color .= chr(0xff);
$color .= chr(0xff);

$c[0] = $color;

$color = '';
$color .= chr(0x00);
$color .= chr(0x00);
$color .= chr(0xff);
$color .= chr(0xff);

$c[1] = $color;

$color = '';
$color .= chr(0x00);
$color .= chr(0xff);
$color .= chr(0x00);
$color .= chr(0xff);

$c[2] = $color;

$color = '';
$color .= chr(0xff);
$color .= chr(0x00);
$color .= chr(0x00);
$color .= chr(0xff);

$c[3] = $color;

for ($i = 0; $i < 4; $i++)
{
	$s->createForData($c[$i], ImageFormat::RGB24, 1, 1, 4);
	$context->setSurface($s, $i % 2, $i / 2);
	$context->paint();
}

$surface->writeToPng(dirname(__FILE__).'/move-to-show-php.png');
