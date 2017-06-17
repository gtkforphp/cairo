<?php

use Cairo\Context;
use Cairo\FillRule;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function littleStarPath($context)
{
	$context->moveTo(10, 0);
	$context->relLineTo(6, 20);
	$context->relLineTo(-16, -12);
	$context->relLineTo(20, 0);
	$context->relLineTo(-16, 12);
}

function bigStarPath($context)
{
	$context->moveTo(40, 0);
	$context->relLineTo(25, 80);
	$context->relLineTo(-65, -50);
	$context->relLineTo(80, 0);
	$context->relLineTo(-65, 50);
	$context->closePath();
}

$surface = new Image(ImageFormat::ARGB32, 163, 103);
$context = new Context($surface);

$context->setSourceRgb(1, 0, 0);
$context->translate(1, 1);
littleStarPath($context);
$context->setFillRule(FillRule::WINDING);
$context->fill();
$context->translate(21, 0);
littleStarPath($context);
$context->setFillRule(FillRule::EVEN_ODD);
$context->fill();
$context->translate(-21, 21);
bigStarPath($context);
$context->setFillRule(FillRule::WINDING);
$context->fill();
$context->translate(81, 0);
bigStarPath($context);
$context->setFillRule(FillRule::EVEN_ODD);
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/fill-rule-php.png');
