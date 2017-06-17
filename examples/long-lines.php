<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$position = 10.5;
$width = 10;
$height = 8;

$surface = new Image(ImageFormat::ARGB32, 70, 70);
$context = new Context($surface);

$line[0] = ['len' => 100.0, 'r' => 1, 'g' => 0, 'b' => 0];
$line[1] = ['len' => 10000.0, 'r' => 0, 'g' => 1, 'b' => 0];
$line[2] = ['len' => 10000.0, 'r' => 0, 'g' => 0, 'b' => 1];
$line[3] = ['len' => 10000.0, 'r' => 1, 'g' => 1, 'b' => 0];
$line[4] = ['len' => 10000.0, 'r' => 0, 'g' => 1, 'b' => 1];
$line[5] = ['len' => 10000.0, 'r' => 1, 'g' => 0, 'b' => 1];

$context->save();
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->restore();
$context->save();
$context->setLineWidth(1);

for ($i = 0; $i < 6; $i++)
{
	$context->moveTo($position, -$line[$i]['len']);
	$context->lineTo($position, $line[$i]['len']);
	$context->setSourceRgb($line[$i]['r'], $line[$i]['g'], $line[$i]['b']);
	$context->stroke();
	$position += 10;
}

$context->restore();
$context->moveTo(35, -10000);
$context->lineTo(35, 10000);
$context->setLineWidth(1);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/long-lines-php.png');
