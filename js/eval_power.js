function
eval_power(p1)
{
	var t, p2;

	expanding--; // undo expanding++ in evalf

	// evaluate exponent

	push(caddr(p1));
	evalf();
	p2 = pop();

	// if exponent is negative then evaluate base without expanding

	push(cadr(p1));

	if (isnegativenumber(p2)) {
		t = expanding;
		expanding = 0;
		evalf();
		expanding = t;
	} else
		evalf();

	push(p2); // push exponent

	power();

	expanding++;
}
