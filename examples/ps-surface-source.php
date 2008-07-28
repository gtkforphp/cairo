<?php

function
draw_pattern ($surface_size)
{
    global $s;
	$con = new CairoContext($s);
	$con->setSourceRgb (1, 1, 1);
    $con->rectangle (0, 0, $surface_size / 2, $surface_size / 2);
    $con->fill ();
    $con->setSourceRgb ( 1, 0, 0);
    $con->rectangle ($surface_size / 2, 0,$surface_size / 2, $surface_size / 2);
    $con->fill ();
    $con->setSourceRgb ( 0, 1, 0);
	$con->rectangle (0, $surface_size / 2, $surface_size / 2, $surface_size / 2);
	$con->fill ();
    $con->setSourceRgb ( 0, 0, 1);
    $con->rectangle ($surface_size / 2, $surface_size / 2, $surface_size / 2, $surface_size / 2);
    $con->fill ();
//	$s->writeToPng(dirname(__FILE__)  . "temp1.png");
}

$size = 90;
$sur = new CairoPSSurface("ps-surface-source.ps", $size, $size);
$sur->setFallbackResolution(72,72);
$con = new CairoContext($sur);

$con->setSourceRgb(0,0,0);
$con->paint();

$surface_size = $size - 30;
$s = new CairoPSSurface("temp.pdf", $surface_size, $surface_size);
draw_pattern($surface_size);
$s->writeToPng(dirname(__FILE__)  . "/temp1.png");
$con->setSourceSurface($s, 15.0, 15.0);
$con->paint();
$sur->writeToPng(dirname(__FILE__)  . "/ps-surface-source-php.png");
?>

