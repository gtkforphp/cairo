<?php
$linewidth = 10.0;
$size = 5*$linewidth;
$pad = 2*$linewidth;

$sur = new CairoImageSurface(FORMAT_ARGB32, 3 * ($pad+$size) + $pad, 3*$pad+2*$size);
$con = new CairoContext($sur);

$dash = array($linewidth, 1.5*$linewidth);
$dashoff = -2*$linewidth;

$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();

for($i = 0; $i<2 ; $i++) {
	$con->save();
	$con->setLineWidth($linewidth);
	$con->setDash($dash, 2, $dashoff);
	$con->translate($pad, $pad);

	$con->moveTo(0,0);
	$con->relLineTo(0,$size);
	$con->relLineTo($size, 0);
	$con->closePath();
	$con->moveTo(2*$linewidth,0);
	$con->relLineTo(3*$linewidth, 0);
	$con->relLineTo(0,3*$linewidth);

	$con->setLineCap(LINE_CAP_BUTT);
	$con->setLineJoin(LINE_JOIN_BEVEL);
	$con->stroke();

	$con->translate($size+$pad, 0);

	$con->moveTo(0,0);
    $con->relLineTo(0,$size);
    $con->relLineTo($size, 0);
    $con->closePath();
    $con->moveTo(2*$linewidth,0);
    $con->relLineTo(3*$linewidth, 0);
    $con->relLineTo(0,3*$linewidth);

    $con->setLineCap(LINE_CAP_ROUND);
    $con->setLineJoin(LINE_JOIN_ROUND);
    $con->stroke();
    $con->translate($size+$pad, 0);
				
    $con->moveTo(0,0);
    $con->relLineTo(0,$size);
    $con->relLineTo($size, 0);
    $con->closePath();
    $con->moveTo(2*$linewidth,0);
    $con->relLineTo(3*$linewidth, 0);
    $con->relLineTo(0,3*$linewidth);

	$con->setLineCap(LINE_CAP_SQUARE);
    $con->setLineJoin(LINE_JOIN_MITER);
    $con->stroke();
	$con->restore();
	$con->translate(0,$size+$pad);
	$dashoff = 0;
	}
	$sur->writeToPng("dash-caps-joins-php.png");
?>
	

