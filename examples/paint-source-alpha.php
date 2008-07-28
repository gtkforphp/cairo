<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 32, 32);
$con = new CairoContext($sur);

$data="";

for($i=0; $i<2;$i++) {
$data.=chr(0x80);
$data.=chr(0x80);
$data.=chr(0x80);
$data.=chr(0x80);

$data.=chr(0x80);
$data.=chr(0x80);
$data.=chr(0x80);
$data.=chr(0x80);

$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0x80);
$data.=chr(0x80);

$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0x80);
$data.=chr(0x80);
}

for($i=0; $i<2;$i++) {
$data.=chr(0x00);
$data.=chr(0x80);
$data.=chr(0x00);
$data.=chr(0x80);

$data.=chr(0x00);
$data.=chr(0x80);
$data.=chr(0x00);
$data.=chr(0x80);

$data.=chr(0x80);
$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0x80);

$data.=chr(0x80);
$data.=chr(0x00);
$data.=chr(0x00);
$data.=chr(0x80);
}
echo $data;
$s = new CairoImageSurface(FORMAT_ARGB32, 100,100);
$s->createFromData($data, FORMAT_ARGB32, 4, 4, 16);
$con->scale(4,4);
$con->setSourceSurface($s,2,2);
$pat = $con->getSource();
$pat->setFilter( FILTER_NEAREST);
$con->paint();

$sur->writeToPng(dirname(__FILE__)  . "/paint-source-alpha-php.png");
?>
