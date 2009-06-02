<?
$width = 12;
$height = 4;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);
$s = new CairoImageSurface(CairoFormat::ARGB32,$width,$height);
$str="";
$stride = $s->getStride();
for($i=0; $i<12; $i++) {
	$str=$str . chr(0x00); //blue
	$str=$str . chr(0x00);//green
    $str=$str . chr(0xff);//red
    $str=$str . chr(0xff);//alpha
    $str=$str . chr(0x00);
    $str=$str . chr(0xff);
    $str=$str . chr(0x00);
    $str=$str . chr(0xff);
    $str=$str . chr(0xff);
    $str=$str . chr(0x00);
    $str=$str . chr(0x00);
    $str=$str . chr(0xff);
    $str=$str . chr(0xff);
    $str=$str . chr(0xff);
    $str=$str . chr(0xff);
    $str=$str . chr(0xff);
}

$s->createForData($str, CairoFormat::ARGB32, $width, $height);
$wid = $s->getHeight();
$con->setSourceRgb(1,1,1);
$con->paint();

$con->setSourceSurface($s,0,0);
//$con->mask_surface($s,0,0);
$con->paint();
$sur->writeToPng(dirname(__FILE__)  . "/bilevel-image-php.png");
?>
