<?php

function draw_symbol($con) {
    $dash = array(6.0, 3.0);
    $con->rectangle(-25, -25, 50, 50);
    $con->stroke();

    $con->moveTo(0, -25);
    $con->curveTo(12.5, -12.5, 12.5, -12.5, 0, 0);
    $con->curveTo(-12.5, 12.5, -12.5, 12.5, 0, 25);
    $con->curveTo(12.5, 12.5, 12.5, 12.5, 0, 0);
    $con->stroke();

    $con->save();

    $con->setDash($dash, 0.);
    $con->moveTo(0, 0);
    $con->arc(0, 0, 12.5, 0, 3 * M_PI / 2);
    $con->closePath();
    $con->stroke();
    $con->restore();
}

$sur = new CairoImageSurface(CairoFormat::ARGB32,200,200);
$con = new CairoContext($sur);

$con->setSourceRgb(1, 1, 1);
$con->paint();
$con->setSourceRgb(0, 0, 0);
$con->save();
$con->translate(50, 50);
$con->scale(1, 1);

draw_symbol($con);
$con->restore();

$con->save();
$con->translate(150, 50);
$con->scale(-1, 1);

draw_symbol($con);
$con->restore();

$con->save();
$con->translate(150, 150);
$con->scale(-1, -1);

draw_symbol($con);
$con->restore();

$con->save();
$con->translate(50, 150);
$con->scale(1, -1);

draw_symbol($con);
$con->restore();

$sur->writeToPng(dirname(__FILE__)  . '/reflected-stroke.png');