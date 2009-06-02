<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 8, 8);
$con = new CairoContext($sur);

$con->setSourceRgb(1,1,1);
$con->paint();

$con->setSourceRgb(0,0,0);
$con->setLineJoin(CairoLineJoin::ROUND);
$con->scale(20.0/100.0, 20/100.);
$con->scale(1./20, 1./20);
$con->setLineWidth(20);
$con->translate ( -18300, -13200);

$con->newPath ();
$con->moveTo ( 18928, 13843);
$con->lineTo ( 18500, 13843);
$con->lineTo ( 18500, 13400);
$con->lineTo ( 18928, 13400);
$con->lineTo ( 18928, 13843);
$con->stroke ();
$sur->writeToPng(dirname(__FILE__)  . "/infinite-join-php.png");
?>

