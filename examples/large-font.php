<?
$width = 800;
$height = 800;
$sur = new CairoImageSurface(FORMAT_ARGB32, $width, $height);
$con = new CairoContext($sur);
$con->setSourceRgb(1,1,1);
$con->paint();
$con->selectFontFace("Bitstream Vera Sans");
$con->setFontSize(10000);
$con->setSourceRgb(0,0,0);
$con->moveTo(-5000, 5000);
$con->showText("xW");

$sur->writeToPng("large-font-php.png");
?>
