<?php

use Cairo\Context;
use Cairo\Operator;
use Cairo\Pattern\Gradient\Linear;
use Cairo\Surface\Content;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$width = 16;
$height = 16;
$pad = 2;
$noperator = 1 + Operator::SATURATE - Operator::CLEAR;
$imagewidth = $noperator * ($width + $pad) + $pad;
$imageheight = 4 * ($height + $pad) + $pad;
$surface = new Image(ImageFormat::ARGB32, $imagewidth, $imageheight);
$context = new Context($surface);
$context->selectFontFace('Bitstream Vera Sans');
$context->setFontSize(0.9 * $height);

for ($i = 0; $i < 4; $i++)
{
	for ($op = Operator::CLEAR; $op < $noperator; $op++)
	{
		$x = $op * ($width + $pad) + $pad;
		$y = $i * ($height + $pad) + $pad;
		
		$context->save();
		$pat = new Linear($x + $width, $y, $x, $y + $height);
		$pat->addColorStopRgba(0.2, 0, 0, 1, 1);
		$pat->addColorStopRgba(0.8, 0, 0, 1, 0);
		
		$context->setPattern($pat);
		$context->rectangle($x, $y, $width, $height);
		$context->fill();
		$context->setOperator($op);
		$context->setSourceRgb(1, 0, 0);
		$context->moveTo($x, $y);
		$context->lineTo($x + $width, $y);
		$context->lineTo($x, $y + $height);
		$context->clip();
		
		switch ($i)
		{
			case 0:
				$wi = floor($width * 0.9);
				$he = floor($height * 0.9);
				$x += 0.05 * $width;
				$y += 0.05 * $height;
				
				$msur = $surface->createSimilar(Content::ALPHA, $wi, $he);
				
				$c2 = new Context($msur);
				$c2->save();
				$c2->setSourceRgba(0, 0, 0, 0);
				$c2->setOperator(Operator::SOURCE);
				$c2->paint();
				$c2->restore();
				
				$c2->setSourceRgb(1, 1, 1);
				$c2->arc(0.5 * $wi, 0.5 * $he, 0.45 * $he, 0, 2 * M_PI);
				$c2->fill();
				
				$context->maskSurface($msur, $x, $y);
				
				break;
			
			case 1:
				$context->setFontSize(0.9 * $height);
				$ext = $context->getTextExtents('FG');
				$context->moveTo($x + floor(($width - $ext['width']) / 2 + 0.5) - $ext['x_bearing'], $y + floor(($height - $ext['height']) / 2 + 0.5) - $ext['y_bearing']);
				$context->showText('FG');
				
				break;
			
			case 2:
				$wi = floor($width * 9 / 10);
				$he = floor($height * 9 / 10);
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
				
				break;
			
			case 3:
				$bw = floor(0.33 * $width + 0.5);
				$bh = floor(0.33 * $height + 0.5);
				
				for ($t1 = 0; $t1 < 3; $t1++)
				{
					for ($t2 = 0; $t2 < 3; $t2++)
					{
						if (($t1 + $t2) % 2 == 0)
						{
							$context->rectangle($x + $bw * $t1, $y + $bh * $t2, $bw, $bh);
						}
					}
					
					$context->fill();
				}
				
				break;
		}
		
		$context->restore();
	}
}

$surface->writeToPng(dirname(__FILE__).'/clip-operator-php.png');
