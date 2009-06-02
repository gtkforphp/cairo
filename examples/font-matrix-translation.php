<?php
function box_text($str, $x, $y)
{
	global $con;
	$con->save();
	$ext = $con->textExtents($str);
	$sf = $con->getScaledFont();
	$sext = $sf->textExtents("text");
	$lw = $con->getLineWidth();
	$con->rectangle($x + $ext["x_bearing"]-$lw/2, $y + $ext["y_bearing"] - $lw/2, $ext["width"]+$lw, $ext["height"]+ $lw);
	$con->stroke();
	$con->moveTo($x,$y);
	$con->showText($str);
	$con->restore();
}
$sur = new CairoImageSurface(CairoFormat::ARGB32, 38, 34);
$con = new CairoContext($sur);

$con->setSourceRgb(1,1,1);
$con->paint();

$con->selectFontFace("Bitstream Vera Sans");
$con->setFontSize(12);
$con->translate(4,4);
$con->setLineWidth(1);
$ext = $con->textExtents("text");

$con->setSourceRgb(0,0,0);
box_text("text", 0, -$ext["y_bearing"]);
$mat = new CairoMatrix();
$mat->translate(6,16);
$mat->scale(12,12);
$con->setFontMatrix($mat);
$con->setSourceRgb(0,0,1);
box_text("text", 0, -$ext["y_bearing"]);

$sur->writeToPng(dirname(__FILE__)  . "/font-matrix-translation-php.png");
?>

