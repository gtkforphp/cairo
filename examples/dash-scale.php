<?php
$linewidth = 8.0;
$size = 5*$linewidth;
$pad = 2*$linewidth;

$imwidth = 3*($pad + $size) + $pad;
$imheight = $size*5 + 6*$pad;

$sur = new CairoImageSurface(CairoFormat::ARGB32, $imwidth, $imheight);
$con = new CairoContext($sur);

$dash= array(1.5*$linewidth);
$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();

$con->translate($pad, $pad);

$con->setDash($dash, -2*$linewidth);
$con->setLineWidth($linewidth);

$con->save();

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::BUTT);
$con->setLineJoin(CairoLineJoin::BEVEL);
$con->stroke();
$con->translate($size+$pad,0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::ROUND);
$con->setLineJoin(CairoLineJoin::ROUND);
$con->stroke();
$con->translate($size+$pad, 0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::SQUARE);
$con->setLineJoin(CairoLineJoin::MITER);
$con->stroke();
$con->restore();

$con->translate(0, $size + 2*$pad);
//$con->save();

$con->save();
$con->scale(1,2);
$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

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
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::ROUND);
$con->setLineJoin(CairoLineJoin::ROUND);
$con->stroke();
$con->translate($size+$pad, 0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::SQUARE);
$con->setLineJoin(CairoLineJoin::MITER);
$con->stroke();
$con->restore();

$con->translate(0, 2*$size + 2*$pad);
$con->save();
$con->scale(1,2);
$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);

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
$con->relLineTo(0, 3 * $linewidth);

$con->setLineCap(CairoLineCap::ROUND);
$con->setLineJoin(CairoLineJoin::ROUND);
$con->stroke();
$con->translate($size+$pad, 0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();
$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0, 3 * $linewidth);
$con->setLineCap(CairoLineCap::SQUARE);
$con->setLineJoin(CairoLineJoin::MITER);
$con->stroke();
$con->restore();

$sur->writeToPng(dirname(__FILE__)  . "/dash-scale-php.png");
?>
