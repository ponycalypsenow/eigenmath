function
emit_arglist(u, p, small_font)
{
	var v = {type:PAREN, a:[]};
	p = cdr(p);
	if (iscons(p)) {
		emit_expr(u, car(p), small_font);
		p = cdr(p);
		while (iscons(p)) {
			emit_roman(u, ",", small_font);
			emit_thin_space(u, small_font);
			emit_expr(u, car(p), small_font);
			p = cdr(p);
		}
	}
	emit_update(v);
	if (small_font)
		v.width += 2 * SMALL_FONT_WIDTH;
	else
		v.width += 2 * FONT_WIDTH;
	u.a.push(v);
}
