<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 10, 10);
$con = new CairoContext($sur);
$con->rectangle(0,0,10,10);
$con->setSourceRgb(0,0,1);
$con->fill();

$con->resetClip();
$con->rectangle(2,2,2,2);
$con->clip();
$con->rectangle(6,6,2,2);
$con->clip();

$con->translate(0.5,0.5);

$con->resetClip();
$con->rectangle(2,2,2,2);
$con->clip();
$con->rectangle(6,6,6,6);
$con->clip();

$con->rectangle(0,0,10,10);
$con->setSourceRgb(1,1,0);
$con->fill();
$con->selectFontFace("Bitstream Vera Sans", CairoFontSlant::NORMAL, CairoFontWeight::NORMAL);
$con->moveTo(0,10);
$con->showText("cairo");
$sur->writeToPng(dirname(__FILE__)  . "/clip-all-php.png");
