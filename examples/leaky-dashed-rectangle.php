<?php
    $width = 60;
    $height = 60;
    $sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
    $con = new CairoContext($sur);
 
    $dash = array(4.0, 2.0);

    $con->setSourceRgb ( 1, 1, 1);
    $con->paint ();

    $con->setSourceRgb ( 0., 0., 0);

    $con->translate ( 0.5, .5);
    $con->setLineWidth ( 1); /* This is vital to reproduce the bug. */

    /* First check simple rectangles */
    $con->setSourceRgb ( 0., 0., 0);
    $con->rectangle ( -$width/4, -$height/4, $width, $height);
    $con->stroke ();
    $con->rectangle ( $width+$width/4, -$height/4, -$width, $height);
    $con->stroke ();
    $con->rectangle ( -$width/4, $height+$height/4, $width, -$height);
    $con->stroke ();
    $con->rectangle ( $width+$width/4, $height+$height/4, -$width, -$height);
    $con->stroke ();

    $con->setDash ( $dash, 0);

    /* And now dashed. */
    $con->setSourceRgb ( 1., 0., 0);
    $con->rectangle ( -$width/4, -$height/4, $width, $height);
    $con->stroke ();
    $con->setSourceRgb ( 0., 1., 0);
    $con->rectangle ( $width+$width/4, -$height/4, -$width, $height);
    $con->stroke ();
    $con->setSourceRgb ( 0., 0., 1);
    $con->rectangle ( -$width/4, $height+$height/4, $width, -$height);
    $con->stroke ();
    $con->setSourceRgb ( 1., 1., 0);
    $con->rectangle ( $width+$width/4, $height+$height/4, -$width, -$height);
    $con->stroke ();
    $sur->writeToPng(dirname(__FILE__)  . "/leaky-dashed-rectangle-php.png");
?>
