<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 256 + 32*2, 192 + 32*2);
$con = new CairoContext($sur);
$s = new CairoImageSurface(CairoFormat::ARGB32,100, 100);
$s->createFromPng(dirname(__FILE__)  . "/romedalen.png");
//$s1 = new CairoImageSurface(FORMATARGB32,100, 100);
$s1 = $sur->createSimilar($sur->getContent(), 320, 256);
$con2 = new CairoContext($s1);
$con2->setSourceSurface($s, 32 ,32);
$con2->setOperator(CairoOperator::SOURCE);
$pat = $con2->getSource();
$pat->setExtend(CairoExtend::REPEAT);
$con2->paint();
$con->setSourceSurface($s1, 0, 0);
$con->paint();
$sur->writeToPng(dirname(__FILE__)  . "/extend-repeat-similar-php.png");
?>

