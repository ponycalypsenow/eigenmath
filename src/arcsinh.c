void
eval_arcsinh(struct atom *p1)
{
	push(cadr(p1));
	eval();
	arcsinh();
}

void
arcsinh(void)
{
	double d;
	struct atom *p1;

	p1 = pop();

	if (isdouble(p1)) {
		push(p1);
		d = pop_double();
		d = asinh(d);
		push_double(d);
		return;
	}

	// arcsinh(z) = log(sqrt(z^2 + 1) + z)

	if (isdoublez(p1)) {
		push(p1);
		push(p1);
		multiply();
		push_double(1.0);
		add();
		sqrtfunc();
		push(p1);
		add();
		logfunc();
		return;
	}

	if (iszero(p1)) {
		push(p1);
		return;
	}

	// arcsinh(-x) = -arcsinh(x)

	if (isnegativeterm(p1)) {
		push(p1);
		negate();
		arcsinh();
		negate();
		return;
	}

	if (car(p1) == symbol(SINH)) {
		push(cadr(p1));
		return;
	}

	push_symbol(ARCSINH);
	push(p1);
	list(2);
}
