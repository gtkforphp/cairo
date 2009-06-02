<?php
function uniform_random($minval, $maxval)
{
	global $state;
	$poly = 0x9a795537;
	$n=32;
	$state = 2*$state < $state ? (2*$state ^ $poly) : 2*$state;
	return floor($minval + $state * ($maxval - $minval) / 4294967296.0);
}

$size = 512;
$numseg = 128;
$width = $size+3;
$height = $size + 3;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $size+3, $size + 3);
$con = new CairoContext($sur);

$con->setSourceRgb(0,0,0);
$con->paint();

$state = 0x123456;

$con->translate(1,1);
$con->setFillRule(CairoFillRule::EVEN_ODD);
$con->moveTo(0,0);

for($i=0; $i<$numseg;$i++) {
$x = uniform_random(0,$width);
$y = uniform_random(0,$height);
$con->lineTo($x,$y);
//echo "x = $x";
//echo "y = $y";
}

$con->closePath();
$con->setSourceRgb(1,0,0);
$con->fillPreserve();
$con->setSourceRgb(0,1,0);
$con->setLineWidth(0.5);
$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . "/random-intersection-php.png");
?>
