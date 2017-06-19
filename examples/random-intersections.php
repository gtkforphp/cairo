<?php

use Cairo\Context;
use Cairo\FillRule;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function uniformRandom($state, $minValue, $maxValue)
{
	$poly = 0x9a795537;
	$state = 2 * $state < $state ? (2 * $state ^ $poly) : 2 * $state;
	
	return floor($minValue + $state * ($maxValue - $minValue) / 4294967296.0);
}

$size = 512;
$segments = 128;
$width = $size + 3;
$height = $size + 3;
$state = 0x123456;

$surface = new Image(ImageFormat::ARGB32, $size + 3, $size + 3);
$context = new Context($surface);

$context->setSourceRgb(0, 0, 0);
$context->paint();

$context->translate(1, 1);
$context->setFillRule(FillRule::EVEN_ODD);
$context->moveTo(0, 0);

for ($i = 0; $i < $segments; $i++)
{
	$x = uniformRandom($state, 0, $width);
	$y = uniformRandom($state, 0, $height);
	$context->lineTo($x, $y);
}

$context->closePath();
$context->setSourceRgb(1, 0, 0);
$context->fillPreserve();
$context->setSourceRgb(0, 1, 0);
$context->setLineWidth(0.5);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/random-intersections-php.png');
