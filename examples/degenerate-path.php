<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 3 * (3 + 6 + 3), 8 * (6 + 3) + 3);
$context = new Context($surface);

$cap = [LineCap::ROUND, LineCap::SQUARE, LineCap::BUTT];
$dash = [2.0, 2.0];
$dash_long = [6.0, 6.0];

$context->setSourceRgb(1, 0, 0);

for ($i = 0; $i < 3; $i++)
{
	$context->save();
	
	$context->setLineCap($cap[$i]);
	
	/* simple degenerate paths */
	$context->setLineWidth(6);
	$context->moveTo(6, 6);
	$context->lineTo(6, 6);
	$context->stroke();
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6, 6);
	$context->closePath();
	$context->stroke();
	
	/* degenerate paths starting with dash on */
	$context->setDash($dash, 0.);
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6, 6);
	$context->lineTo(6, 6);
	$context->stroke();
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6, 6);
	$context->closePath();
	$context->stroke();
	
	/* degenerate paths starting with dash off */
	/* these should not draw anything */
	$context->setDash($dash, 2.);
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6, 6);
	$context->lineTo(6, 6);
	$context->stroke();
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6, 6);
	$context->closePath();
	$context->stroke();
	
	/* this should draw a single degenerate sub-path
	 * at the end of the path */
	$context->setDash($dash_long, 6.);
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6 + 6.0, 6);
	$context->lineTo(6, 6);
	$context->stroke();
	
	/* this should draw a single degenerate sub-path
	 * at the end of the path. The difference between this
	 * and the above is that this ends with a degenerate sub-path*/
	$context->setDash($dash_long, 6.0);
	
	$context->translate(0, 3 * 3);
	$context->moveTo(6 + 6.0, 6);
	$context->lineTo(6, 6);
	$context->lineTo(6, 6);
	$context->stroke();
	
	$context->restore();
	
	$context->translate(3 + 6 + 3, 0);
}

$surface->writeToPng(dirname(__FILE__).'/degenerate-path-php.png');
