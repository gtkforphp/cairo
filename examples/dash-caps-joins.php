<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\LineJoin;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$linewidth = 10.0;
$size = 5 * $linewidth;
$pad = 2 * $linewidth;

$surface = new Image(ImageFormat::ARGB32, 3 * ($pad + $size) + $pad, 3 * $pad + 2 * $size);
$context = new Context($surface);

$dash = [$linewidth, 1.5 * $linewidth];
$dashoff = -2 * $linewidth;

$context->save();
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->restore();

for ($i = 0; $i < 2; $i++)
{
	$context->save();
	$context->setLineWidth($linewidth);
	$context->setDash($dash, $dashoff);
	$context->translate($pad, $pad);
	
	$context->moveTo(0, 0);
	$context->relLineTo(0, $size);
	$context->relLineTo($size, 0);
	$context->closePath();
	$context->moveTo(2 * $linewidth, 0);
	$context->relLineTo(3 * $linewidth, 0);
	$context->relLineTo(0, 3 * $linewidth);
	
	$context->setLineCap(LineCap::BUTT);
	$context->setLineJoin(LineJoin::BEVEL);
	$context->stroke();
	
	$context->translate($size + $pad, 0);
	
	$context->moveTo(0, 0);
	$context->relLineTo(0, $size);
	$context->relLineTo($size, 0);
	$context->closePath();
	$context->moveTo(2 * $linewidth, 0);
	$context->relLineTo(3 * $linewidth, 0);
	$context->relLineTo(0, 3 * $linewidth);
	
	$context->setLineCap(LineCap::ROUND);
	$context->setLineJoin(LineJoin::ROUND);
	$context->stroke();
	$context->translate($size + $pad, 0);
	
	$context->moveTo(0, 0);
	$context->relLineTo(0, $size);
	$context->relLineTo($size, 0);
	$context->closePath();
	$context->moveTo(2 * $linewidth, 0);
	$context->relLineTo(3 * $linewidth, 0);
	$context->relLineTo(0, 3 * $linewidth);
	
	$context->setLineCap(LineCap::SQUARE);
	$context->setLineJoin(LineJoin::MITER);
	$context->stroke();
	$context->restore();
	$context->translate(0, $size + $pad);
	$dashoff = 0;
}

$surface->writeToPng(dirname(__FILE__).'/dash-caps-joins-php.png');
