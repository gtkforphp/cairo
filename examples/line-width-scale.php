<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function splinePath($spline, $context)
{
	$context->save();
	$context->moveTo(-$spline, 0);
	$context->curveTo(-$spline / 4, -$spline, $spline / 4, $spline, $spline, 0);
	$context->restore();
}

function scaleThenSetLineWidthAndStroke($context, $spline, $scaleX, $scaleY, $lineWidth)
{
	$context->scale($scaleX, $scaleY);
	$context->setLineWidth($lineWidth);
	splinePath($spline, $context);
	$context->stroke();
}

function scalePathAndLineWidth($context, $spline, $scaleX, $scaleY, $lineWidth)
{
	$context->save();
	$context->scale($scaleX, $scaleY);
	splinePath($spline, $context);
	$context->restore();
	$context->save();
	$context->scale($scaleX, $scaleY);
	$context->setLineWidth($lineWidth);
	$context->stroke();
	$context->restore();
}

function setLineWidthThenScaleAndStroke($context, $spline, $scaleX, $scaleY, $lineWidth)
{
	$context->setLineWidth($lineWidth);
	$context->scale($scaleX, $scaleY);
	splinePath($spline, $context);
	$context->stroke();
}

function scalePathNotLineWidth($context, $spline, $scaleX, $scaleY, $lineWidth)
{
	$context->save();
	$context->scale($scaleX, $scaleY);
	splinePath($spline, $context);
	$context->restore();
	$context->save();
	$context->setLineWidth($lineWidth);
	$context->stroke();
	$context->restore();
}

$spline = 50.0;
$lineWidth = 13;
$scaleX = 0.5;
$scaleY = 2.0;
$width = ($scaleX * $spline * 6.0);
$height = ($scaleY * $spline * 2.0);

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);
$context->setSourceRgb(1.0, 1.0, 1.0); /* white */
$context->paint();
$context->setSourceRgb(0.0, 0.0, 0.0); /* black */

for ($i = 0; $i < 4; $i++)
{
	$context->save();
	
	switch ($i)
	{
		case 0:
			$context->translate($width / 4, $height / 4);
			scaleThenSetLineWidthAndStroke($context, $spline, $scaleX, $scaleY, $lineWidth);
			break;
		case 1:
			$context->translate($width / 4 + $width / 2, $height / 4);
			scalePathAndLineWidth($context, $spline, $scaleX, $scaleY, $lineWidth);
			break;
		case 2:
			$context->translate($width / 4, $height / 4 + $height / 2);
			setLineWidthThenScaleAndStroke($context, $spline, $scaleX, $scaleY, $lineWidth);
			break;
		case 3:
			$context->translate($width / 4 + $width / 2, $height / 4 + $height / 2);
			scalePathNotLineWidth($context, $spline, $scaleX, $scaleY, $lineWidth);
			break;
	}
	
	$context->restore();
}

$surface->writeToPng(dirname(__FILE__).'/line-width-scale-php.png');
