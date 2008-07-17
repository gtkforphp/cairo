<?
$sur = new CairoImageSurface(FORMAT_ARGB32, 10, 10);
$con = new CairoContext($sur);

$data="";
for($i = 0; $i<4; $i++) {
	$data = $data . chr(0x80);
    $data = $data . chr(0x00);
    $data = $data . chr(0x00);
    $data = $data . chr(0x00);
}

$s = new CairoImageSurface(FORMAT_ARGB32,1,1);
$s->createFromData(data,FORMAT_ARGB32, 2, 2, 8);
//$pat = new CairoSurfacePattern($s);
$con->setSourceRgb(1,0,0);

$con->save();
$con->translate(2,2);
$con->maskSurface($s,0,0);
$con->restore();

$con->maskSurface($s,4,4);

//$mat = new CairoMatrix();
$con->translate(2,2);
//$pat->setMatrix($mat);

$con->maskSurface($s,4,4);


$sur->writeToPng("mask-surface-ctm-php.png");
?>



