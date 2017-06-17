<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 100;
$border = 10;
$linewidth = 20;

$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);
$s = $context->getGroupSurface();

$c = new Context($s);
$c->moveTo($border, $border);
$c->lineTo($border + $linewidth, $border);
$c->lineTo($size - $border, $size - $border);
$c->lineTo($size - $border - $linewidth, $size - $border);

$c->clip();
$c->setSourceRgb(0, 0, 1);
$c->paint();

$c->setSourceRgb(1, 1, 1);
$c->rectangle(($size / 2) - ($linewidth / 2), $border, $linewidth, ($size - 2) * $border);
$c->fill();

$c2 = new Context($surface);
$c2->setSourceRgb(1, 1, 1);
$c2->rectangle($size - $border - $linewidth, $border, $linewidth, ($size - 2) * $border);
$c2->fill();

$context->setSourceRgb(1, 1, 1);
$context->rectangle($border, $border, $linewidth, ($size - 2) * $border);
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/clip-nesting-php.png');




