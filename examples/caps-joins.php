<?php
$linewidth = 10.0;
$size = 5 * $linewidth;
$pad = 2 * $linewidth;
$width = 3*($pad + $size) + $pad;
$height = $pad + $size + $pad;
$sur = new CairoImageSurface(CairoFormat::ARGB32,$width, $height);
$con = new CairoContext($sur);
$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();

$con->setLineWidth($linewidth);
$con->translate($pad, $pad);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();

$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0,3*$linewidth);

$con->setLineCap(CairoLineCap::BUTT);
$con->setLineJoin(CairoLineJoin::BEVEL);
$con->stroke();

$con->translate($size+$pad, 0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();

$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0,3*$linewidth);

$con->setLineCap(CairoLineCap::ROUND);
$con->setLineJoin(CairoLineJoin::ROUND);
$con->stroke();

$con->translate($size+$pad,0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();

$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0,3*$linewidth);

$con->setLineCap(CairoLineCap::SQUARE);
$con->setLineJoin(CairoLineJoin::MITER);
$con->stroke();
$sur->writeToPng(dirname(__FILE__) . "/caps-joins-php.png");
?>




