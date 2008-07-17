<?
$sur = new CairoImageSurface(FORMAT_ARGB32, 256 + 32*2, 192 + 32*2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_ARGB32,100, 100);
$s->createFromPng("romedalen.png");
//$s1 = new CairoImageSurface(FORMAT_ARGB32,100, 100);
$s1 = $sur->createSimilar($sur->get_content(), 320, 256);
$con2 = new CairoContext($s1);
$con2->setSourceSurface($s, 32 ,32);
$con2->setPperator(OPERATOR_SOURCE);
$pat = $con2->getSource();
$pat->setExtend(EXTEND_REPEAT);
$con2->paint();
$con->setSourceSurface($s1, 0, 0);
$con->paint();
$sur->writeToPng("extend-repeat-similar-php.png");
?>

