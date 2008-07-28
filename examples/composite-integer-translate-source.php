<?php
$sur = new CairoImageSurface(FORMAT_ARGB32,100, 100);
$con = new CairoContext($sur);

$s = new CairoImageSurface(FORMAT_ARGB32,1,1);
$s->createFromPng(dirname(__FILE__)  . "/romedalen.png");

$con->setSourceRgb(0,0,0);
$con->rectangle(0,0,100,100);
$con->fill();

$con->translate(10,10);
$con->setOperator(OPERATOR_SOURCE);
$con->setSourceSurface($s,0,0);
$con->rectangle(0,0,90,90);
$con->fill();
$sur->writeToPng(dirname(__FILE__)  . "/composite-integer-translate-source-php.png");
?>

