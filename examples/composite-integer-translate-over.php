<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32,100, 100);
$con = new CairoContext($sur);

$s = new CairoImageSurface(CairoFormat::ARGB32,1,1);
$s->createFromPng(dirname(__FILE__)  . "/romedalen.png");

$con->setSourceRgb(0,0,0);
$con->rectangle(0,0,100,100);
$con->fill();

$con->translate(10,10);
$con->setOperator(CairoOperator::OVER);
$con->setSourceSurface($s,0,0);
$con->rectangle(0,0,90,90);
$con->fill();
$sur->writeToPng(dirname(__FILE__)  . "/composite-integer-translate-over-php.png");
?>

