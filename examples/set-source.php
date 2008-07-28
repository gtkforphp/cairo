<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 5, 5);
$con = new CairoContext($sur);

$color = "";
$color.= chr(0x4c);
$color.= chr(0x33);
$color.= chr(0x19);
$color.= chr(0x80);

$s = new CairoImageSurface(FORMAT_ARGB32, 1, 1);
$s->createFromData($color, FORMAT_ARGB32, 1,1,4);

$pat = new CairoSurfacePattern($s);
$pat->setExtend(EXTEND_REPEAT);

for($i=0; $i<5; $i++) {
switch($i) {
case 0:
	$con->setSourceRgb(.6,.7,.8);
	break;
case 1:
	$con->setSourceRgba(.2,.4,.6,.5);
	break;
case 2:
	$con->setSourceRgba(.2,.4,.6,.5);
	break;
case 3:
default:
	$con->setSource($pat);
}

$con->rectangle($i,0,1,5);
$con->fill();
}
$sur->writeToPng(dirname(__FILE__)  . "/set-source-php.png");
?>

