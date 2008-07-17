<?
function little_star_path()
{
	global $con;
	$con->moveTo(10,0);
	$con->relLineTo(6,20);
	$con->relLineTo(-16,-12);
	$con->relLineTo(20,0);
	$con->relLineTo(-16,12);
}

function big_star_path()
{
	global $con;
    $con->moveTo(40,0);
    $con->relLineTo(25,80);
    $con->relLineTo(-65,-50);
    $con->relLineTo(80,0);
    $con->relLineTo(-65,50);
	$con->closePath();
}

$sur = new CairoImageSurface(FORMAT_ARGB32, 163, 103);
$con = new CairoContext($sur);
$con->setSourceRgb(1,0,0);
$con->translate(1,1);
little_star_path();
$con->setFillRule(FILL_RULE_WINDING);
$con->fill();
$con->translate(21,0);
little_star_path();
$con->setFillRule(FILL_RULE_EVEN_ODD);
$con->fill();
$con->translate(-21, 21);
big_star_path();
$con->setFillRule(FILL_RULE_WINDING);
$con->fill();
$con->translate(81,0);
big_star_path();
$con->setFillRule(FILL_RULE_EVEN_ODD);
$con->fill();
$sur->writeToPng("fill-rule-php.png");
?>


