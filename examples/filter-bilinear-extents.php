<?
$sur = new CairoImageSurface(FORMAT_ARGB32, 36, 36);
$con = new CairoContext($sur);
$s = new CairoImageSurface(FORMAT_ARGB32, 2, 2);
$con2 = new CairoContext($s);
$con2->setSourceRgb(1,0,0);
$con2->paint();
$con2->setSourceRgb(0,0,1);
$con2->rectangle(0,1,1,1);
$con2->rectangle(1,0,1,1);
$con2->fill();
$con->setSourceRgb(0,0,0);
$con->paint();
$con->save();
$con->translate(3,3);
$con->scale(10,10);
$con->translate(0.5,0.5);
$con->setSourceSurface($s,0,0);
$con->paint();
$con->restore();
$sur->writeToPng("filter-bilinear-extents-php.png");
?>


