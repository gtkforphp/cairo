<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 2, 2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_ARGB32, 2, 2);

$s->createFromPng("create-from-png-ref.png");
$con->setSourceSurface($s);
$con->paint();

$sur->writeToPng("create-from-png-php.png");
?>
