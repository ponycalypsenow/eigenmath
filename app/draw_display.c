#include "app.h"

void
draw_display(double y1, double y2)
{
	double y;
	struct display *p;
	y = 0.0;
	p = first;
	while (p) {
		draw_display_nib(p, y, y1, y2);
		y += p->height;
		if (p == fence)
			break;
		p = p->next;
	}
}
