#include "defs.h"

void
eval_sum(void)
{
	int i, j, k;

	// 1st arg (quoted)

	p1 = cdr(p1);
	p2 = car(p1);
	if (!issymbol(p2))
		stop("sum: 1st arg?");

	// 2nd arg

	p1 = cdr(p1);
	push(car(p1));
	eval();
	j = pop_integer();
	if (j == ERR)
		stop("sum: 2nd arg?");

	// 3rd arg

	p1 = cdr(p1);
	push(car(p1));
	eval();
	k = pop_integer();
	if (k == ERR)
		stop("sum: 3rd arg?");

	if (k - j < 0) {
		push(zero);
		return;
	}

	// 4th arg

	p1 = cadr(p1);

	push_binding(p2);

	for (i = j; i <= k; i++) {
		push_integer(i);
		p3 = pop();
		set_binding(p2, p3);
		push(p1);
		eval();
	}

	add_terms(k - j + 1);

	p1 = pop();
	pop_binding(p2);
	push(p1);
}
