<?php
	$sur = new CairoImageSurface(CairoFormat::ARGB32,90, 90);
	$con = new CairoContext($sur);

    $surface_size = (90 - 30) / 10;
    $con->setSourceRgba ( 0, 0, 0, 1);
    $con->rectangle ( 0, 0, 90, 90);
    $con->fill ();
    $surface = new CairoImageSurface(CairoFormat::RGB24,
					  $surface_size, $surface_size);
    $con2 = new CairoContext($surface);
    $con2->setSourceRgb ( 1, 1, 1);
    $con2->rectangle (
		     0, 0,
		     $surface_size / 2, $surface_size / 2);
    $con2->fill ();
    $con2->setSourceRgb ( 1, 0, 0);
    $con2->rectangle (
		     $surface_size / 2, 0,
		     $surface_size / 2, $surface_size / 2);
    $con2->fill ();
    $con2->setSourceRgb ( 0, 1, 0);
    $con2->rectangle (
		     0, $surface_size / 2,
		     $surface_size / 2, $surface_size / 2);
    $con2->fill ();
    $con2->setSourceRgb ( 0, 0, 1);
    $con2->rectangle (
		     $surface_size / 2, $surface_size / 2,
		     $surface_size / 2, $surface_size / 2);
    $con2->fill ();

    $con->scale ( 10, 10);
    $con->setSourceSurface ( $surface, 1.5, 1.5);
    
    /* Using EXTEND_REFLECT makes this test pass for image and xlib backends */
	$pattern = $con->getSource();
    $pattern->setExtend(CairoExtend::PAD);
    $con->rectangle ( 1.5, 1.5, 6, 6);
    $con->clip ();
	$con->setSource($pattern);
    $con->paint ();
	$sur->writeToPng(dirname(__FILE__)  . "/extend-pad-php.png");



?>
