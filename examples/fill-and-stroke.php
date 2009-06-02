<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 28, 14);
$con = new CairoContext($sur);
$con->rectangle(2,2,10,10);
$con->setSourceRgb(0,0,1);
$con->fillPreserve();
$con->setSourceRgb(1,0,0);
$con->stroke();

$con->translate(14,0);
$con->arc(7, 7, 5, 0, 2*M_PI);
$con->fillPreserve();
$con->setSourceRgb(0,0,1);
$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . "/fill-and-stroke-php.png");
?>

