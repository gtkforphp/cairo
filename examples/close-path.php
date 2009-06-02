<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 32, 16);
$con = new CairoContext($sur);

$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();

$con->arc(8, 8, 4, 0, M_PI);
$con->closePath();
$con->arc(8,8,4,M_PI,2*M_PI);
$con->fill();

$con->translate(16,0);
$con->moveTo(8,4);
$con->arcNegative(8,8,4,3*M_PI/2,M_PI/2);
$con->closePath();
$con->curveTo(12,4,12,12,8,12);

$path = $con->copyPathFlat();
$con->newPath();
$con->appendPath($path);
$con->fill();

$sur->writeToPng(dirname(__FILE__)  . "/close-path-php.png");
?>

