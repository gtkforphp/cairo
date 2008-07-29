<?php
$sur = new CairoImageSurface(Cairo::FORMAT_ARGB32, 20, 20);
$con = new CairoContext($sur);

$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();

$con->setLineWidth(4);
$con->setLineCap(Cairo::LINE_CAP_ROUND);
$con->moveTo(4,4);
$con->lineTo(4,16);
$con->moveTo(10,4);
$con->lineTo(10,16);
$con->moveTo(16,4);
$con->lineTo(16,16);

$con->stroke();
$sur->writeToPng(dirname(__FILE__)  . "/caps-sub-paths-php.png");
?>
