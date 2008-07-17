<?
$sur = new CairoImageSurface(FORMAT_ARGB32, 2, 2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_ARGB32, 2, 2);
$file = fopen("create-from-png-ref.png","r");
$s->createFromPngStream($file);
$con->setSourceSurface($s);
$con->paint();

$sur->writeToPng("create-from-png-stream-php.png");
?>
