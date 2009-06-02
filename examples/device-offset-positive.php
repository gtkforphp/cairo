<?php
$size = 10;
$pad = 2;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
$con = new CairoContext($sur);

$con->setSourceRgb(0,0,1);
$con->rectangle($pad, $pad, $size - 2*$pad, $size - 2*$pad);
$con->fill();

$s = $con->getGroupTarget();
$c = $s->getContent();
$s1 = $s->createSimilar($c, $size/2, $size/2);

$c = new CairoContext($s1);
$c->setSourceRgb(1,0,0);
$c->rectangle($pad, $pad, $size - 2*$pad, $size - 2*$pad);
$c->fill();

$s1->setDeviceOffset($size/2, $size/2);
$con->setSourceSurface($s1, $size/2, $size/2);
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/device-offset-positive-php.png");

?>
