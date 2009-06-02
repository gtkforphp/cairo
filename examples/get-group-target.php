<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 8, 8);
$con = new CairoContext($sur);
$con->save();
$con->setSourceRgb(0,0,1);
$con->paint();

$con->rectangle(2,2,4,4);
$con->clip();
$con->setSourceRgb(1,0,0);
$con->paint();
$con->restore();
$con->pushGroup();
$s = $con->getGroupTarget();

$con->setSourceRgb(0,1,0);
$con->fill();
$off = $s->getDeviceOffset();
$te = $off["x"];
echo $te;
$con->rectangle(2, 2, 4, 4);
$con->fill();
$con->popGroupToSource();
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/get-group-target-php.png");

?>

