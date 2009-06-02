<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 40, 40);
$con = new CairoContext($sur);

$con->setSourceRgb(1,1,1);
$con->paint();
$con->setLineCap(CairoLineCap::ROUND);
$con->setLineWidth(5);
$con->setSourceRgb(0,1,0);

for($n=0;$n<8;$n++) {
    $theta = $n * 2 * M_PI / 8;
    $con->newSubPath();
    $con->arc(20, 20, 15, $theta, $theta);
    $con->closePath();
}

$con->stroke();

$con->setLineWidth(2);
$con->setSourceRgb(0,0,1);

for($n=0;$n<8;$n++) {
    $theta = $n * 2 * M_PI / 8;
    $con->moveTo(20,20);
    $con->arc(20,20,15, $theta, $theta);
    $con->closePath();
}

$con->stroke();
$con->setSourceRgb(1,0,0);
$con->arc(20,20,2,0,2*M_PI);
$con->fill();

$sur->writeToPng(dirname(__FILE__)  . '/degenerate-arc.png');