<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 25*60, 4*60);
$con = new CairoContext($sur);

$dash = array(20.0,20.0);

$con->setSourceRgb(0, 0, 0);
$con->paint();

for($a=0; $a<4; $a++)
for($b=0; $b<5; $b++)
for($c=0; $c<5; $c++) {

    $con->moveTo((($b*5)+$c)*60 + 10, $a*60 + 10);
    $con->relCurveTo(0, $b*10, 0, $b*10, $c*10, $b*10);
    $con->setSourceRgb(1,1,1);
    $con->setLineWidth(8);
    $con->setLineCap(CairoLineCap::ROUND);
    $con->setDash($dash, $a*10);
    $con->strokePreserve();
    $con->setSourceRgb(0,0.5,1);
    $con->setLineWidth(2);
    $con->setLineCap(2);
    $ar = array(8.0,8.0);
    $con->setDash($ar,0);
    $con->stroke();
}

$sur->writeToPng(dirname(__FILE__)  . '/dash-curve-php.png');