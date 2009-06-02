<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 6, 6);
$con = new CairoContext($sur);

$data="";

for($i=0; $i<2;$i++) {
$data.=chr(0xff);
$data.=chr(0xff);
$data.=chr(0xff);
$data.=chr(0xff);

$data.=chr(0xff);
$data.=chr(0xff);
$data.=chr(0xff);
$data.=chr(0xff);

$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0xff);
$data.=chr(0xff);

$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0xff);
$data.=chr(0xff);
}

for($i=0; $i<2;$i++) {
$data.=chr(0x00);
$data.=chr(0xff);
$data.=chr(0x00);
$data.=chr(0xff);

$data.=chr(0x00);
$data.=chr(0xff);
$data.=chr(0x00);
$data.=chr(0xff);

$data.=chr(0xff);
$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0xff);

$data.=chr(0xff);
$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0xff);
}
$con->setSourceRgb(0,0,0);
$con->paint();

$s = new CairoImageSurface(CairoFormat::ARGB32, 100,100);
$s->createForData($data, CairoFormat::RGB24, 4, 4, 16);
//$con->test_paint_checkered();
$con->scale(0.5,0.5);
$con->setSourceSurface($s,4,4);
$pat = $con->getSource();
$pat->setFilter( CairoFilter::NEAREST);
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/scale-down-source-surface-paint-php.png");
?>
