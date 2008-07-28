<?php
$width = 100;
$height = 100;
$sur = new CairoPSSurface("temp.ps", $width, $height);
$con = new CairoContext($sur);

$con->setSourceRgb(0,0,1);
$con->moveTo(50,50);
$con->lineTo(50000,50000);
$con->stroke();

$con->setSourceRgb(0,1,0);
$con->moveTo(50,50);
$con->lineTo(-50000,50000);
$con->stroke();

$con->setSourceRgb(1,0,0);
$con->moveTo(50,50);
$con->lineTo(50000,-50000);
$con->stroke();

$con->setSourceRgb(1,1,0);
$con->moveTo(50,50);
$con->lineTo(-50000,-50000);
$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . "/big-line-php.png");
?>
