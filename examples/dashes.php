<?php
$dashes = array(50.0,  /* ink */
                   10.0,  /* skip */
                   10.0,  /* ink */
                   10.0   /* skip*/
                   );
$ndash  = count($dashes);
$offset = -50.0;
$sur = new CairoImageSurface(0,500,500);
$con = new CairoContext($sur);
$con->setDash ($dashes, $offset);
$con->setLineWidth (10.0);
$con->moveTo (128.0, 25.6);
$con->lineTo ( 230.4, 230.4);
$con->relLineTo ( -102.4, 0.0);
$con->curveTo ( 51.2, 230.4, 51.2, 128.0, 128.0, 128.0);
$con->stroke ();
$sur->writeToPng(dirname(__FILE__)  . "/image_dash.png");
?>
