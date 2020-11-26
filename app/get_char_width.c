#include "app.h"

double
get_char_width(int font_num, int char_num)
{
	double w;
	CTFontRef f;
	CFStringRef s;
	CGGlyph g;

	f = get_font_ref(font_num);
	s = get_char_name(char_num);
	g = CTFontGetGlyphWithName(f, s);

	w = CTFontGetAdvancesForGlyphs(f, kCTFontOrientationHorizontal, &g, NULL, 1);

	return w;
}
