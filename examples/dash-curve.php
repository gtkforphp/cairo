<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$dash = [20.0, 20.0];

$surface = new Image(ImageFormat::ARGB32, 25 * 60, 4 * 60);
$context = new Context($surface);

$context->setSourceRgb(0, 0, 0);
$context->paint();

for ($a = 0; $a < 4; $a++)
{
	for ($b = 0; $b < 5; $b++)
	{
		for ($c = 0; $c < 5; $c++)
		{
			$context->moveTo((($b * 5) + $c) * 60 + 10, $a * 60 + 10);
			$context->relCurveTo(0, $b * 10, 0, $b * 10, $c * 10, $b * 10);
			$context->setSourceRgb(1, 1, 1);
			$context->setLineWidth(8);
			$context->setLineCap(LineCap::ROUND);
			$context->setDash($dash, $a * 10);
			$context->strokePreserve();
			$context->setSourceRgb(0, 0.5, 1);
			$context->setLineWidth(2);
			$context->setLineCap(2);
			$ar = [8.0, 8.0];
			$context->setDash($ar, 0);
			$context->stroke();
		}
	}
}

$surface->writeToPng(dirname(__FILE__).'/dash-curve-php.png');
