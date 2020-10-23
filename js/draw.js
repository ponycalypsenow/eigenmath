function
draw(F, X)
{
	draw_xrange();
	draw_yrange();

	var h = DRAW_HEIGHT + 4 * DRAW_PAD;
	var w = DRAW_INDENT + DRAW_WIDTH + 4 * DRAW_PAD;

	h = "height='" + h + "'";
	w = "width='" + w + "'";

	outbuf = "<p><svg " + h + w + ">\n"

	draw_xaxis();
	draw_yaxis();
	draw_box();
	draw_labels();

	draw_array = [];

	draw_pass1(F, X);
	draw_pass2(F, X);

	outbuf += "</svg></p>\n";

	stdout.innerHTML += outbuf;
}