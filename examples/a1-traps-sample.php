<?php
$points = 10.0;
$step = 1.0/ $points;
$pad = 1.0;
$width = ($pad + ($points*2) + $pad);
$height = $width;
$sur = new CairoImageSurface(CairoFormat::ARGB32,$width,$height);
$con = new CairoContext($sur);
$con->setSourceRgb(1,1,1);
$con->paint();

$con->setSourceRgb(0,0,0);
$con->translate($pad, $pad);
$con->setAntialias(CairoAntialias::MODE_NONE);

for($i = 0; $i < $points; $i++)
	for($j = 0; $j < $points; $j++) {
		$t1 = (2 * $i * 1.0) + (($i) * $step * 2.0);
		$t2 = (2 * $j * 1.0) + (($j) * $step * 1.0);
		$con->rectangle($t1, $t2, 1, 1);
		$con->fill();
	}
$sur->writeToPng(dirname(__FILE__)  . '/a1-traps-sample-php.png');
?>


