<?php
	$size = 20;
	$pad = 2;
	$surface_size = sqrt(($size - 2*$pad)*($size-2*$pad)/2);
	$sur = new CairoImageSurface(CairoFormat::ARGB32, $size, $size);
    $con = new CairoContext($sur);
	$s = new CairoImageSurface(CairoFormat::RGB24,
					  $surface_size, $surface_size);
    $con2 = new CairoContext($s);
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
    

    /* First paint opaque background (black) so we don't need separate
     * ARGB32 and RGB24 reference images. */
    $con->setSourceRgb ( 0, 0, 0); /* black */
    $con->paint ();

    $con->translate( $size/2, $size/2);
    $con->rotate ( M_PI / 4.0);
    $con->translate ( -$surface_size/2, -$surface_size/2);

    $con->setSourceSurface ( $s, 0, 0);
    $pat = $con->getSource();

	$pat->setFilter(CairoFilter::NEAREST);
    $con->setSource($pat);
	$con->paint ();
	$sur->writeToPng(dirname(__FILE__)  . "/rotate-image-surface-paint-php.png");


?>
