<?php
$cisize = 10;
$pad = 2;
$width = $cisize*6.5 + $pad;
$height = $cisize*3.5 + $pad;

function draw_circle($x, $y)
{
	global $con, $cisize;
	$con->save();
	$con->translate($x,$y);
	$con->arc(0,0,$cisize / 2,0,2*M_PI);
	$con->fill();
	$con->restore();
}

function draw_circles()
{
	global $con, $cisize;
	draw_circle(0, $cisize*-0.1);
	draw_circle($cisize*0.4, $cisize*0.25);
	draw_circle($cisize*2,0);
	draw_circle($cisize*4,0);
	draw_circle($cisize*6,0);
}

$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);

$con->translate($pad, $pad);
$con->setSourceRgb(0,1,0);
$con->setOperator(CairoOperator::OVER);
draw_circle($cisize*0.5, $cisize*1.5);
$con->setSourceRgb(1,0,0);
$con->setOperator(CairoOperator::ADD);
draw_circle($cisize*0.75, $cisize*1.75);
$con->setSourceRgb(0,1,0);
$con->setOperator(CairoOperator::OVER);
$con->translate($cisize*2.5, $cisize*0.6);
draw_circles();
$con->setSourceRgb(1,0,0);
$con->setOperator(CairoOperator::ADD);
$con->translate(0, $cisize*2);
draw_circles();

$sur->writeToPng(dirname(__FILE__)  . "/finer-grained-fallbacks-php.png");
?>

