<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 2, 2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(CairoFormat::ARGB32, 2, 2);
$file = fopen(dirname(__FILE__)  ."/create-from-png-ref.png","r");
$s->createFromPng($file);
$con->setSourceSurface($s);
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/create-from-png-stream-php.png");
?>
