<?php
$sur = new CairoImageSurface(CairoFormat::RGB24, 2, 2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(CairoFormat::RGB24, 2, 2);
$c = array();

$color="";
$color.=chr(0xff);
$color.=chr(0xff);
$color.=chr(0xff);
$color.=chr(0xff);

$c[0]= $color;

$color = "";
$color.=chr(0x00);
$color.=chr(0x00);
$color.=chr(0xff);
$color.=chr(0xff);

$c[1] = $color;

$color = "";
$color.=chr(0x00);
$color.=chr(0xff);
$color.=chr(0x00);
$color.=chr(0xff);

$c[2] = $color;

$color = "";
$color.=chr(0xff);
$color.=chr(0x00);
$color.=chr(0x00);
$color.=chr(0xff);

$c[3] = $color;


for($i =0 ; $i<4;$i++)
{
	$s ->createForData($c[$i], CairoFormat::RGB24, 1 , 1, 4);
	$con->setSourceSurface($s, $i%2, $i/2);
	$con->paint();
}


$sur->writeToPng(dirname(__FILE__)  . "/move-to-show-surface-php.png");
?>
