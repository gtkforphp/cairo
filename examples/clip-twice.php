<?php
$width = 64;
$height = 64;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);
$con->newPath();
$con->arc($width/2, $height/2, $width/3, 0, 2 * M_PI);
$con->clip();
$con->newPath();
$con->moveTo(0,0);
$con->lineTo($width/4, $height/2);
$con->lineTo(0, $height);
$con->lineTo($width, $height);
$con->lineTo(3*$width/4, $height/2);
$con->lineTo($width, 0);
$con->closePath();
$con->clip();
$con->setSourceRgb(0,0,0.6);
$con->newPath();
$con->moveTo(0,0);
$con->lineTo(0, $height);
$con->lineTo($width/2, 3*$height/4);
$con->lineTo($width, $height);
$con->lineTo($width, 0);
$con->lineTo($width/2, $height/4);
$con->closePath();
$con->fill();
$con->newPath();
$con->arc($width/2, $height/2, $width/5, 0, 2 * M_PI);
$con->clip();
$con->setSourceRgb(1,1,0);
$con->paint();


$sur->writeToPng(dirname(__FILE__)  . "/clip-twice-php.png");
?>
