<?php
$sur = new CairoImageSurface(CairoFormat::RGB24,165, 30);
$con = new CairoContext($sur);
$con->moveTo(0,0);

	$con->setSourceRgb ( 1, 1, 1);
    $con->paint ();

    $con->setSourceRgb ( 0, 0, 0);
	$con->moveTo(0,0);
    $con->translate ( 5, 5);

    /* First compress the pen to a vertical line. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->scale ( 0.00001, 1.0);
	$con->stroke ();
    }
    $con->restore ();

    $con->translate ( 5 + 20, 0);

    /* Then compress the pen to a horizontal line. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->scale ( 1.0, 0.00001);
	$con->stroke ();
    }
    $con->restore ();

    $con->translate ( 5 + 20, 0);

    /* Finally a line at an angle. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->rotate ( M_PI / 4.0);
	$con->scale ( 0.00001, 1.0);
	$con->stroke ();
    }
    $con->restore ();
$con->setSourceRgb ( 1, 1, 1);
    $con->paint ();

    $con->setSourceRgb ( 0, 0, 0);
    $con->setLineJoin (CairoLineJoin::ROUND);

    $con->translate ( 5, 5);

    /* First compress the pen to a vertical line. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->scale ( 0.00001, 1.0);
	$con->stroke ();
    }
    $con->restore ();

    $con->translate ( 5 + 20, 0);

    /* Then compress the pen to a horizontal line. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->scale ( 1.0, 0.00001);
	$con->stroke ();
    }
    $con->restore ();

    $con->translate ( 5 + 20, 0);

    /* Finally a line at an angle. */
    $con->rectangle ( 0, 0, 20, 20);
    $con->curveTo ( 20 / 2, 0, 20, 20 / 2, 20, 20);
    $con->save ();
    {
	$con->rotate ( M_PI / 4.0);
	$con->scale ( 0.00001, 1.0);
	$con->stroke ();
    }
    $con->restore ();
	$sur->writeToPng(dirname(__FILE__)  . "/degenerate-pen-php.png"); 
?>
