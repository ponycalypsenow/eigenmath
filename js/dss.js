function
dss(F, X)
{
	if (!isusersymbol(X))
		stopf("derivative: symbol expected");

	// d(x,x)?

	if (equal(F, X)) {
		push_integer(1);
		return;
	}

	// d(a,x)?

	if (!iscons(F)) {
		push_integer(0);
		return;
	}

	if (car(F) == symbol(ADD)) {
		dsum(F, X);
		return;
	}

	if (car(F) == symbol(MULTIPLY)) {
		dproduct(F, X);
		return;
	}

	if (car(F) == symbol(POWER)) {
		dpower(F, X);
		return;
	}

	if (car(F) == symbol(DERIVATIVE)) {
		dd(F, X);
		return;
	}

	if (car(F) == symbol(LOG)) {
		dlog(F, X);
		return;
	}

	if (car(F) == symbol(SIN)) {
		dsin(F, X);
		return;
	}

	if (car(F) == symbol(COS)) {
		dcos(F, X);
		return;
	}

	if (car(F) == symbol(TAN)) {
		dtan(F, X);
		return;
	}

	if (car(F) == symbol(ARCSIN)) {
		darcsin(F, X);
		return;
	}

	if (car(F) == symbol(ARCCOS)) {
		darccos(F, X);
		return;
	}

	if (car(F) == symbol(ARCTAN)) {
		darctan(F, X);
		return;
	}

	if (car(F) == symbol(SINH)) {
		dsinh(F, X);
		return;
	}

	if (car(F) == symbol(COSH)) {
		dcosh(F, X);
		return;
	}

	if (car(F) == symbol(TANH)) {
		dtanh(F, X);
		return;
	}

	if (car(F) == symbol(ARCSINH)) {
		darcsinh(F, X);
		return;
	}

	if (car(F) == symbol(ARCCOSH)) {
		darccosh(F, X);
		return;
	}

	if (car(F) == symbol(ARCTANH)) {
		darctanh(F, X);
		return;
	}

	if (car(F) == symbol(ERF)) {
		derf(F, X);
		return;
	}

	if (car(F) == symbol(INTEGRAL) && caddr(F) == X) {
		push(cadr(F));
		return;
	}

	dfunction(F, X);
}
