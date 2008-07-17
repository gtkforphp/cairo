<?
$linewidth = 10.0;
$size = 5 * $linewidth;
$pad = 2 * $linewidth;
$width = 3*($pad + $size) + $pad;
$height = $pad + $size + $pad;
$sur = new CairoImageSurface(FORMAT_ARGB32,$width, $height);
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

$con->setLineCap(LINE_CAP_BUTT);
$con->setLineJoin(LINE_JOIN_BEVEL);
$con->stroke();

$con->translate($size+$pad, 0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();

$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0,3*$linewidth);

$con->setLineCap(LINE_CAP_ROUND);
$con->setLineJoin(LINE_JOIN_ROUND);
$con->stroke();

$con->translate($size+$pad,0);

$con->moveTo(0,0);
$con->relLineTo(0,$size);
$con->relLineTo($size,0);
$con->closePath();

$con->moveTo(2*$linewidth, 0);
$con->relLineTo(3*$linewidth, 0);
$con->relLineTo(0,3*$linewidth);

$con->setLineCap(LINE_CAP_SQUARE);
$con->setLineJoin(LINE_JOIN_MITER);
$con->stroke();
$sur->writeToPng("caps-joins-php.png");
?>




