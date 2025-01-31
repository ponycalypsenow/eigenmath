void
eval_mod(struct atom *p1)
{
	push(cadr(p1));
	eval();

	push(caddr(p1));
	eval();

	modfunc();
}

void
modfunc(void)
{
	double d1, d2;
	struct atom *p1, *p2;

	p2 = pop();
	p1 = pop();

	if (!isnum(p1) || !isnum(p2) || iszero(p2)) {
		push_symbol(MOD);
		push(p1);
		push(p2);
		list(3);
		return;
	}

	if (isrational(p1) && isrational(p2)) {
		mod_rationals(p1, p2);
		return;
	}

	push(p1);
	d1 = pop_double();

	push(p2);
	d2 = pop_double();

	push_double(fmod(d1, d2));
}

void
mod_rationals(struct atom *p1, struct atom *p2)
{
	if (isinteger(p1) && isinteger(p2)) {
		mod_integers(p1, p2);
		return;
	}
	push(p1);
	push(p1);
	push(p2);
	divide();
	absfunc();
	floorfunc();
	push(p2);
	multiply();
	if (p1->sign == p2->sign)
		negate();
	add();
}

void
mod_integers(struct atom *p1, struct atom *p2)
{
	push_bignum(p1->sign, mmod(p1->u.q.a, p2->u.q.a), mint(1));
}
