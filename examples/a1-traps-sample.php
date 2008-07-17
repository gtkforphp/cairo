<?
$points = 10.0;
$step = 1.0/ $points;
$pad = 1.0;
$width = ($pad + ($points*2) + $pad);
$height = $width;
$sur = new CairoImageSurface(FORMAT_ARGB32,$width,$height);
//$s = new CairoImageSurface(FORMAT_ARGB32,1,1);
//$s->create_from_data($n, FORMAT_ARGB32, 1, 1, 4);
$con = new CairoContext($sur);
//$c = new CairoContext($s);
//$c->set_source_rgb(0,0,0);
//$c->paint();
$con->setSourceRgb(1,1,1);
$con->paint();

$con->setSourceRgb(0,0,0);
$con->translate($pad, $pad);
$con->setAntialias(ANTIALIAS_NONE);

for($i = 0; $i < $points; $i++)
	for($j = 0; $j < $points; $j++) {
		$t1 = (2 * $i * 1.0) + (($i) * $step * 2.0);
		$t2 = (2 * $j * 1.0) + (($j) * $step * 1.0);
		//$con->set_source_surface($s, $t1, $t2);
		//$pat = $con->get_source();
		//$pat->set_filter(FILTER_NEAREST);
		$con->rectangle($t1, $t2, 1, 1);
		$con->fill();
	}
$sur->writeToPng('a1-traps-sample-php.png');
?>


