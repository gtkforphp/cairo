<?php

use Cairo\Antialias;
use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$points = 10;
$step = 1.0 / $points;
$pad = 1;
$width = ($pad + ($points * 2) + $pad);
$height = $width;

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setSourceRgb(0, 0, 0);
$context->translate($pad, $pad);
$context->setAntialias(Antialias::NONE);

for ($i = 0; $i < $points; $i++)
{
	for ($j = 0; $j < $points; $j++)
	{
		$t1 = (2 * $i) + (($i + 1) * $step);
		$t2 = (2 * $j) + (($j + 1) * $step);
		
		$context->rectangle($t1, $t2, 1, 1);
		$context->fill();
	}
}

$surface->writeToPng(dirname(__FILE__).'/a1-traps-sample-php.png');


