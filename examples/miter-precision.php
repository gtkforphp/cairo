<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 120, 100);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setSourceRgb(0, 0, 0);
$context->setMiterLimit(100000);

for ($xscale = 1; $xscale <= 1000; $xscale += 999)
{
	for ($yscale = 1; $yscale <= 1000; $yscale += 999)
	{
		$max_scale = max($xscale, $yscale);
		$context->save();
		
		if ($xscale > 1)
		{
			$context->translate(50, 0);
		}
		
		if ($yscale > 1)
		{
			$context->translate(0, 50);
		}
		
		$context->scale($xscale, $yscale);
		$context->setLineWidth(10.0 / $max_scale);
		$context->moveTo(10.0 / $xscale, 10.0 / $yscale);
		$context->lineTo(40.0 / $xscale, 10.0 / $yscale);
		$context->lineTo(10.0 / $xscale, 30.0 / $yscale);
		$context->stroke();
		$context->restore();
	}
}

$surface->writeToPng(dirname(__FILE__).'/miter-precision-php.png');
