<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32,100, 100);
$con = new CairoContext($sur);

$s = new CairoImageSurface(CairoFormat::ARGB32,20, 20);
$con2 = new CairoContext($s);

$con2->setSourceRgba(1,0,0,1);
$con2->rectangle(0,0,10,10);
$con2->fill();
$con2->setSourceRgba(0,1,0,1);
$con2->rectangle(10,0,10,10);
$con2->fill();
$con2->setSourceRgba(0,0,1,1);
$con2->rectangle(0,10,10,10);
$con2->fill();
$con2->setSourceRgba(1,1,0,1);
$con2->rectangle(10,10,10,10);
$con2->fill();

$pat = new CairoSurfacePattern($s);
$pat->setExtend(CairoExtend::REPEAT);
$con->setSourceRgba(0,0,0,1);
$con->rectangle(0,0,100,100);
$con->fill();
$con->translate(10,10);
$con->setOperator(CairoOperator::OVER);
$con->setSource($pat);
$con->rectangle(0,0,90,90);
$con->fill();
$sur->writeToPng(dirname(__FILE__) . "/composite-integer-translate-over-repeat-php.png");
?>


