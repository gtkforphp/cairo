<?php

$points = 10;

$step = 1.0/ $points;

$pad = 1;

$width = ($pad + ($points*2) + $pad);

$height = $width;

$sur = new CairoImageSurface(CairoFormat::ARGB32,$width,$height);

$s = new CairoImageSurface(CairoFormat::ARGB32,1,1);

$con = new CairoContext($sur);

$c = new CairoContext($s);

$c->setSourceRgb(0,0,0);

$c->paint();

$con->setSourceRgb(1,1,1);

$con->paint();



$con->setSourceRgb(0,0,0);

$con->translate($pad, $pad);

$con->setAntialias(CairoAntialias::MODE_NONE);



for($i = 0; $i < $points; $i++)

	for($j = 0; $j < $points; $j++) {

		$t1 = (2 * $i) + (($i+1) * $step);

		$t2 = (2 * $j) + (($j+1) * $step);

		$con->setSourceSurface($s, $t1, $t2);

		$pat = $con->getSource();

		$pat->setFilter(CairoFilter::NEAREST);

		$con->paint();

	}

$sur->writeToPng(dirname(__FILE__)  . '/a1-image-sample-php.png');

?>





