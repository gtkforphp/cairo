<?php
$starsize = 20;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $starsize * 2 + 2, $starsize+2);
$con = new CairoContext($sur);
$con->setSourceRgb(1,0,0);
$con->translate(1,1);
$con->save();

$con->moveTo(10, 0);
$con->relLineTo ( 6, 20);
$con->relLineTo ( -16, -12);
$con->relLineTo ( 20, 0);
$con->relLineTo ( -16, 12);

$con->setFillRule (CairoFillRule::WINDING);
$con->clip ();
$con->paint ();

$con->restore ();
$con->translate ($starsize + 1, 0);
$con->save ();

$con->moveTo(10, 0);
$con->relLineTo ( 6, 20);
$con->relLineTo ( -16, -12);
$con->relLineTo ( 20, 0);
$con->relLineTo ( -16, 12);

$con->setFillRule (CairoFillRule::EVEN_ODD);
$con->clip ();
$con->paint ();

$con->restore();
$sur->writeToPng(dirname(__FILE__) . "/clip-fill-rule-php.png");
?>

