<?php

use Cairo\Context;
use Cairo\FontSlant;
use Cairo\FontWeight;
use Cairo\Operator;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Surface\Content;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

function setSolidPattern($context, $x, $y)
{
	$context->setSourceRgb(1.0, 0, 0.0);
}

function setGradientPttern($context, $width, $height, $x, $y)
{
	$pat = new Linear($x, $y, $x + $width, $y + $height);
	$pat->addColorStopRgba(0.2, 1, 0, 0, 1);
	$pat->addColorStopRgba(0.8, 1, 0, 0, 0.0);
	$context->setPattern($pat);
	
}

function drawMask($surface, $context, $width, $height, $x, $y)
{
	$wi = floor(0.9 * $width);
	$he = floor(0.9 * $height);
	$x += 0.05 * $width;
	$y += 0.05 * $height;
	
	$s = $surface->createSimilar(Content::ALPHA, $wi, $he);
	$con2 = new Context($s);
	$con2->setSourceRgb(1, 1, 1); /* white */
	$con2->arc(0.5 * $wi, 0.5 * $he, 0.45 * $he, 0, 2 * M_PI);
	$con2->fill();
	
	$context->maskSurface($s, $x, $y);
}

function drawGlyphs($context, $width, $height, $x, $y)
{
	$context->setFontSize(0.8 * $height);
	$extents = $context->textExtents('FG');
	
	$moveX = $x + floor(($width - $extents['width']) / 2 + 0.5) - $extents['x_bearing'];
	$moveY = $y + floor(($height - $extents['height']) / 2 + 0.5) - $extents['y_bearing'];
	
	$context->moveTo($moveX, $moveY);
	$context->showText('FG');
}

function drawPolygon($context, $width, $height, $x, $y)
{
	$wi = floor(0.9 * $width);
	$he = floor(0.9 * $height);
	$x += 0.05 * $width;
	$y += 0.05 * $height;
	
	$context->newPath();
	$context->moveTo($x, $y);
	$context->lineTo($x, $y + $he);
	$context->lineTo($x + $wi / 2, $y + 3 * $he / 4);
	$context->lineTo($x + $wi, $y + $he);
	$context->lineTo($x + $wi, $y);
	$context->lineTo($x + $wi / 2, $y + $he / 4);
	$context->closePath();
	$context->fill();
}

function drawRects($context, $width, $height, $x, $y)
{
	$blockWidth = floor(0.33 * $width + 0.5);
	$blockHeight = floor(0.33 * $height + 0.5);
	
	for ($i = 0; $i < 3; $i++)
	{
		for ($j = 0; $j < 3; $j++)
		{
			if (($i + $j) % 2 == 0)
			{
				$context->rectangle($x + $blockWidth * $i, $y + $blockHeight * $j, $blockWidth, $blockHeight);
			}
		}
	}
	
	$context->fill();
}

$width = 16;
$height = 16;
$pad = 2;

$imageWidth = 2 * ($width + $pad) + $pad;
$imageHeight = 4 * ($height + $pad) + $pad;

$surface = new Image(ImageFormat::ARGB32, $imageWidth, $imageHeight);
$context = new Context($surface);
$context->selectFontFace('Bitstream Vera Sans', FontSlant::NORMAL, FontWeight::NORMAL);

for ($j = 0; $j < 4; $j++)
{
	for ($i = 0; $i < 2; $i++)
	{
		$x = $i * ($width + $pad) + $pad;
		$y = $j * ($height + $pad) + $pad;
		
		$context->save();
		
		$pat = new Linear($x + $width, $y, $x, $y + $height);
		$pat->addColorStopRgba(0.2, 0.0, 0.0, 1.0, 1.0); /* Solid blue */
		$pat->addColorStopRgba(0.8, 0.0, 0.0, 1.0, 0.0); /* Transparent blue */
		$context->setPattern($pat);
		
		$context->rectangle($x, $y, $width, $height);
		$context->fillPreserve();
		$context->clip();
		
		$context->setOperator(Operator::CLEAR);
		
		switch ($i)
		{
			case 0:
				setSolidPattern($context, $x, $y);
				break;
			case 1:
				setGradientPttern($context, $width, $height, $x, $y);
				break;
		}
		
		switch ($j)
		{
			case 0:
				drawMask($surface, $context, $width, $height, $x, $y);
				break;
			case 1:
				drawGlyphs($context, $width, $height, $x, $y);
				break;
			case 2:
				drawPolygon($context, $width, $height, $x, $y);
				break;
			case 3:
				drawRects($context, $width, $height, $x, $y);
				break;
		}
		$context->restore();
	}
}

$surface->writeToPng(dirname(__FILE__).'/operator-clear-php.png');
