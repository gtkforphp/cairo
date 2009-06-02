<?php
$width = 10;
$height = 8;
$sur = new CairoImageSurface(CairoFormat::ARGB32, 70, 70);
$con = new CairoContext($sur);

$line[0] = array('len'=>100.0, 'r'=>1, 'g'=>0, 'b'=>0);
$line[1] = array('len'=>10000.0, 'r'=>0, 'g'=>1, 'b'=>0);
$line[2] = array('len'=>10000.0, 'r'=>0, 'g'=>0, 'b'=>1);
$line[3] = array('len'=>10000.0, 'r'=>1, 'g'=>1, 'b'=>0);
$line[4] = array('len'=>10000.0, 'r'=>0, 'g'=>1, 'b'=>1);
$line[5] = array('len'=>10000.0, 'r'=>1, 'g'=>0, 'b'=>1);

$con->save();
$con->setSourceRgb(1,1,1);
$con->paint();
$con->restore();
$con->save();
$con->setLineWidth(1);

$pos = 10.5;
for($i =0; $i < 6; $i++) {
    $con->moveTo($pos, -$line[$i]['len']);
    $con->lineTo($pos, $line[$i]['len']);
    $con->setSourceRgb($line[$i]['r'], $line[$i]['g'], $line[$i]['b']);
    $con->stroke();
    $pos+=10;
}

$con->restore();
$con->moveTo(35, -10000);
$con->lineTo(35,  10000);
$con->setLineWidth(1);

$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . '/long-lines.png');