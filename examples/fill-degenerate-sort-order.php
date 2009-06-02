<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 190, 120);
$con = new CairoContext($sur);

$con->setSourceRgb(1,0,0);
$con->moveTo(43,103);
$con->lineTo(91,101);
$con->lineTo(0,112);
$con->lineTo(60,0);
$con->lineTo(91,101);
$con->lineTo(43,103);
$con->lineTo(176,110);
$con->lineTo(116,100);
$con->lineTo(176,0);
$con->lineTo(176,110);
$con->closePath();
$con->fill();
$sur->writeToPng(dirname(__FILE__)  . "/fill-degenerate-sort-order-php.png");
?>

