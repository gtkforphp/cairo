<?php
$size = 100;
$border = 10;
$linewidth = 20;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
$con = new CairoContext($sur);
$s = $con->getGroupTarget();
$c = new CairoContext($s);

$c->moveTo($border, $border);
$c->lineTo($border + $linewidth, $border);
$c->lineTo($size - $border, $size - $border);
$c->lineTo($size - $border-$linewidth, $size - $border);

$c->clip();
$c->setSourceRgb(0,0,1);
$c->paint();

$c->setSourceRgb(1,1,1);
$c->rectangle($size/2 - $linewidth/2, $border, $linewidth, $size - 2*$border);
$c->fill();

$c2 = new CairoContext($sur);
$c2->setSourceRgb(1,1,1);
$c2->rectangle($size - $border - $linewidth, $border, $linewidth, $size - 2 * $border);
$c2->fill();

$con->setSourceRgb(1,1,1);
$con->rectangle($border, $border, $linewidth, $size - 2 * $border);
$con->fill();

$sur->writeToPng(dirname(__FILE__)  . "/clip-nesting-php.png");




