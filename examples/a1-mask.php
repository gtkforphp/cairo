<?php
$width = 10;
$height = 8;
$sur = new CairoImageSurface(FORMAT_ARGB32, $width, $height);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_A1,$width,$height);
$str="";
$stride = $s->getStride();

for($i=0; $i<8; $i++) {
	$str=$str . chr(0x14);
	$str=$str . chr(0xAA);
	/*$str=$str . chr(255);
	$str=$str . chr(0);
	$str=$str . chr(255);
	$str=$str . chr(0);
	$str=$str . chr(0);
	$str=$str . chr(0);*/
}

echo $str;
$s->createFromData($str, FORMAT_A1, $width, $height);
$con->setSourceRgb(0,0,1);
$con->paint();

$con->setSourceRgb(1,0,0);
$con->maskSurface($s,0,0);
$sur->writeToPng("a1-mask-php.png");
?>
