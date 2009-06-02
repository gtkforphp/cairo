<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32,20,20);
$redmask = 0x5;
$greenmask = 0x50;
$con = new CairoContext($sur);
$con->setSourceRgb(0,0,1);
$con->paint();
$s = new CairoImageSurface(CairoFormat::A1, 6400,20);
$stride = $s->getStride();
$height = $s->getHeight();
$width = $s->getWidth();
$data = "";
for($y = 0; $y<$height; $y++) {
	for($x=0; $x<($width+7)/8; $x++)
		$data = $data . chr(5);
}
$s->createForData($data,CairoFormat::A1,$width, $height, $stride);
$con->setSourceRgb(1,0,0);
$con->maskSurface($s);
$con->fill();
$s = new CairoImageSurface(CairoFormat::A1,20, 6400);
$stride = $s->getStride();
$height = $s->getHeight();
$width = $s->getWidth();
$data = "";
for($y = 0; $y<$height; $y++) {
    for($x=0; $x<($width+7)/8; $x++)
        $data = $data . chr(80);
	}
$s->createForData($data,CairoFormat::A1,$width, $height, $stride);
$con->setSourceRgb(0,1,0);
$con->maskSurface($s,0,0);

$sur->writeToPng(dirname(__FILE__)  . "/large-source-php.png");
?>
