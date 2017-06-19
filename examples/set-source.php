<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Pattern\Surface as PatternSurface;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 5, 5);
$context = new Context($surface);

$color = '';
$color .= chr(0x4c);
$color .= chr(0x33);
$color .= chr(0x19);
$color .= chr(0x80);

$s = new Image(ImageFormat::ARGB32, 1, 1);
$s->createForData($color, ImageFormat::ARGB32, 1, 1, 4);

$pat = new PatternSurface($s);
$pat->setExtend(Extend::REPEAT);

for ($i = 0; $i < 5; $i++)
{
	switch ($i)
	{
		case 0:
			$context->setSourceRgb(.6, .7, .8);
			break;
		case 1:
			$context->setSourceRgba(.2, .4, .6, .5);
			break;
		case 2:
			$context->setSourceRgba(.2, .4, .6, .5);
			break;
		case 3:
		default:
			$context->setPattern($pat);
	}
	
	$context->rectangle($i, 0, 1, 5);
	$context->fill();
}

$surface->writeToPng(dirname(__FILE__).'/set-source-php.png');
