<?php
	$size = 25;
	$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
	$con = new CairoContext($sur);
/* Paint background white, then draw in black. */
    $con->setSourceRgb (1.0, 1.0, 1.0); /* white */
    $con->paint ();
    $con->setSourceRgb (0.0, 0.0, 0.0); /* black */

    $con->setLineWidth (1.0);
    $con->translate (1, 1);

    /* Draw everything first with square caps. */
    $con->setLineCap (CairoLineCap::SQUARE);

    /* Draw horizontal and vertical segments, each in both
     * directions. */
    $con->moveTo     ( 4.5,  0.5);
    $con->relLineTo ( 2.0,  0.0);

    $con->moveTo     (10.5,  4.5);
    $con->relLineTo ( 0.0,  2.0);

    $con->moveTo     ( 6.5, 10.5);
    $con->relLineTo (-2.0,  0.0);

    $con->moveTo     ( 0.5,  6.5);
    $con->relLineTo ( 0.0, -2.0);

    /* Draw right angle turns in four directions. */
    $con->moveTo     ( 0.5,  2.5);
    $con->relLineTo ( 0.0, -2.0);
    $con->relLineTo ( 2.0,  0.0);

    $con->moveTo     ( 8.5,  0.5);
    $con->relLineTo ( 2.0,  0.0);
    $con->relLineTo ( 0.0,  2.0);

    $con->moveTo     (10.5,  8.5);
    $con->relLineTo ( 0.0,  2.0);
    $con->relLineTo (-2.0,  0.0);

    $con->moveTo     ( 2.5, 10.5);
    $con->relLineTo (-2.0,  0.0);
    $con->relLineTo ( 0.0, -2.0);

    /* Draw a closed-path rectangle */
    $con->rectangle   (0.5, 12.5, 10.0, 10.0);

    $con->stroke ();

    $con->translate (12, 0);

    /* Now draw the same results, but with butt caps. */
    $con->setLineCap (CairoLineCap::BUTT);

    /* Draw horizontal and vertical segments, each in both
     * directions. */
    $con->moveTo     ( 4.0,  0.5);
    $con->relLineTo ( 3.0,  0.0);

    $con->moveTo     (10.5,  4.0);
    $con->relLineTo ( 0.0,  3.0);

    $con->moveTo     ( 7.0, 10.5);
    $con->relLineTo (-3.0,  0.0);

    $con->moveTo     ( 0.5,  7.0);
    $con->relLineTo ( 0.0, -3.0);

    /* Draw right angle turns in four directions. */
    $con->moveTo     ( 0.5,  3.0);
    $con->relLineTo ( 0.0, -2.5);
    $con->relLineTo ( 2.5,  0.0);

    $con->moveTo     ( 8.0,  0.5);
    $con->relLineTo ( 2.5,  0.0);
    $con->relLineTo ( 0.0,  2.5);

    $con->moveTo     (10.5,  8.0);
    $con->relLineTo ( 0.0,  2.5);
    $con->relLineTo (-2.5,  0.0);

    $con->moveTo     ( 3.0, 10.5);
    $con->relLineTo (-2.5,  0.0);
    $con->relLineTo ( 0.0, -2.5);

    /* Draw a closed-path rectangle */
    $con->rectangle   (0.5, 12.5, 10.0, 10.0);

    /* Draw a path that is rectilinear initially, but not completely */
    /* We draw this out of the target window.  The bug that caused this
     * addition was leaks if part of the path was rectilinear but not
     * completely */
    $con->moveTo     ( 3.0, 30.5);
    $con->relLineTo (-2.5,  0.0);
    $con->relLineTo (+2.5, +2.5);

    $con->stroke ();
	$sur->writeToPng(dirname(__FILE__)  . "/rectilinear-stroke-php.png");
?>
