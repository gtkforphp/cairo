<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 256 + 32*2, 192 + 32*2);
$con = new CairoContext($sur);

$s = new CairoImageSurface(FORMAT_ARGB32,1,1);
$s->createFromPng("romedalen.png");

$con->setSourceSurface($s,32,32);

$pat = $con->getSource();
$pat->setExtend(EXTEND_REFLECT);
$con->paint();

$sur->writeToPng("extend-reflect-php.png");
?>
