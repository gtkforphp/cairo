<?php
	$sur = new CairoImageSurface(Cairo::FORMAT_ARGB32, 12, 12);
	$con = new CairoContext($sur);
    $source = $sur->createSimilar (
                       Cairo::CONTENT_COLOR_ALPHA,
                       12, 12);

    $con2 = new CairoContext($source);

    /* Fill the source surface with green */
    
    $con2->setSourceRgb ( 0, 1, 0);
    $con2->paint ();

    /* Draw a blue square in the middle of the source with clipping,
     * and leave the clip there. */
    $con2->rectangle (
             12 / 4, 12 / 4,
             12 / 2, 12 / 2);
    $con2->clip ();
    $con2->setSourceRgb ( 0, 0, 1);
    $con2->paint ();

    /* Fill the destination surface with solid red (should not appear
     * in final result) */
    $con->setSourceRgb ( 1, 0, 0);
    $con->paint ();

    /* Now draw the source surface onto the destination surface */
    $con->setSourceSurface ( $source, 0, 0);
    $con->paint ();
	$sur->writeToPng(dirname(__FILE__)  . "/source-clip-php.png");
	

?>
