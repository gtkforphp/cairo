<?
$sur = new CairoImageSurface(FORMAT_ARGB32, 256 + 32*2, 192+ 32*2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_ARGB32,100, 100);
$s->createFromPng("romedalen.png");
$con->setSourceSurface($s,32,32);
$pat = $con->getSource();
$pat->setExtend(EXTEND_REPEAT);
$con->setSource($pat);
$con->paint();

$sur->writeToPng("extend-repeat-php.png");
?>

