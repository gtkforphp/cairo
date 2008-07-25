<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 10, 10);
$con = new CairoContext($sur);
$con->setSourceRgb(0,0,1);
$con->paint();

$con->resetClip();
$con->clip();

$con->translate(0.5,0.5);

$con->setSourceRgb(0,1,0);
$con->rectangle(0,0,10,10);
$con->fillPreserve();
$con->setSourceRgb(1,0,0);
$con->stroke();
$con->selectFontFace("Bitstream Vera Sans", FONT_SLANT_NORMAL, FONT_WEIGHT_NORMAL);
$con->moveTo(0,10);
$con->showText("cairo");
$sur->writeToPng("clip-empty-php.png");
?>
