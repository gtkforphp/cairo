<?php
$size = 10;
$pad = 2;

$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
$con = new CairoContext($sur);

$con->setSourceRgb(1,0,0);
$con->paint();

$con->arc($size/2, $size/2, $size/2 - $pad, 0, 2*M_PI);
$con->clip();
$con->pushGroup();
$con->setSourceRgb(0,0,1);
$con->paint();
$con->popGroupToSource();
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/clip-push-group-php.png");
?>
