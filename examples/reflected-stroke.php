<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function drawSymbol($context)
{
	$dash = [6.0, 3.0];
	
	$context->rectangle(-25, -25, 50, 50);
	$context->stroke();
	
	$context->moveTo(0, -25);
	$context->curveTo(12.5, -12.5, 12.5, -12.5, 0, 0);
	$context->curveTo(-12.5, 12.5, -12.5, 12.5, 0, 25);
	$context->curveTo(12.5, 12.5, 12.5, 12.5, 0, 0);
	$context->stroke();
	
	$context->save();
	
	$context->setDash($dash, 0.);
	$context->moveTo(0, 0);
	$context->arc(0, 0, 12.5, 0, 3 * M_PI / 2);
	$context->closePath();
	$context->stroke();
	$context->restore();
}

$surface = new Image(ImageFormat::ARGB32, 200, 200);
$context = new Context($surface);

$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->setSourceRgb(0, 0, 0);
$context->save();
$context->translate(50, 50);
$context->scale(1, 1);

drawSymbol($context);
$context->restore();

$context->save();
$context->translate(150, 50);
$context->scale(-1, 1);

drawSymbol($context);
$context->restore();

$context->save();
$context->translate(150, 150);
$context->scale(-1, -1);

drawSymbol($context);
$context->restore();

$context->save();
$context->translate(50, 150);
$context->scale(1, -1);

drawSymbol($context);
$context->restore();

$surface->writeToPng(dirname(__FILE__).'/reflected-stroke-php.png');