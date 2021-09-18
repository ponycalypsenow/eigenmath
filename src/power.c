#include "defs.h"

#undef BASE
#undef EXPO
#undef R
#undef X
#undef Y
#undef PX
#undef PY

#define BASE p3
#define EXPO p4
#define R p5
#define X p6
#define Y p7
#define PX p8
#define PY p9

void
eval_power(void)
{
	int t;
	push(caddr(p1)); // exponent
	eval();
	p2 = pop();
	if (isnegativenumber(p2)) {
		// don't expand in denominators
		t = expanding;
		expanding = 0;
		push(cadr(p1)); // base
		eval();
		push(p2);
		power();
		expanding = t;
	} else {
		push(cadr(p1)); // base
		eval();
		push(p2);
		power();
	}
}

void
power(void)
{
	save();
	power_nib();
	restore();
}

void
power_nib(void)
{
	int h, i, n;

	EXPO = pop();
	BASE = pop();

	if (istensor(BASE)) {
		power_tensor();
		return;
	}

	if (BASE == symbol(EXP1) && isdouble(EXPO)) {
		push_double(M_E);
		BASE = pop();
	}

	if (BASE == symbol(PI) && isdouble(EXPO)) {
		push_double(M_PI);
		BASE = pop();
	}

	if (isnum(BASE) && isnum(EXPO)) {
		power_numbers();
		return;
	}

	// expr^0

	if (iszero(EXPO)) {
		push_integer(1);
		return;
	}

	// 0^expr

	if (iszero(BASE)) {
		push_symbol(POWER);
		push(BASE);
		push(EXPO);
		list(3);
		return;
	}

	// expr^1

	if (isplusone(EXPO)) {
		push(BASE);
		return;
	}

	// 1^expr

	if (isplusone(BASE)) {
		push(BASE);
		return;
	}

	// BASE is an integer? (EXPO is not numerical)

	if (isinteger(BASE)) {
		// raise each factor in BASE to power EXPO
		h = tos;
		push(BASE);
		factor_factor();
		n = tos - h;
		for (i = 0; i < n; i++) {
			p1 = stack[h + i];
			if (car(p1) == symbol(POWER)) {
				push_symbol(POWER);
				push(cadr(p1)); // base
				push(caddr(p1)); // expo
				push(EXPO);
				multiply();
				list(3);
			} else {
				push_symbol(POWER);
				push(p1);
				push(EXPO);
				list(3);
			}
			stack[h + i] = pop();
		}
		if (n > 1) {
			sort_factors(n);
			list(n);
			push_symbol(MULTIPLY);
			swap();
			cons();
		}
		return;
	}

	// BASE is a numerical fraction? (EXPO is not numerical)

	if (isfraction(BASE)) {
		// power numerator, power denominator
		push(BASE);
		numerator();
		push(EXPO);
		power();
		push(BASE);
		denominator();
		push(EXPO);
		negate();
		power();
		multiply();
		return;
	}

	// BASE = e ?

	if (BASE == symbol(EXP1)) {
		power_natural_number();
		return;
	}

	// do this before checking for (a + b)^n

	if (iscomplexnumber(BASE) && isnum(EXPO)) {
		power_complex_number();
		return;
	}

	// (a + b)^n -> (a + b) * (a + b) ...

	if (car(BASE) == symbol(ADD)) {
		power_sum();
		return;
	}

	// (a * b) ^ c -> (a ^ c) * (b ^ c)

	if (car(BASE) == symbol(MULTIPLY)) {
		h = tos;
		p1 = cdr(BASE);
		while (iscons(p1)) {
			push(car(p1));
			push(EXPO);
			power();
			p1 = cdr(p1);
		}
		multiply_factors(tos - h);
		return;
	}

	// (a^b)^c -> a^(b * c)

	if (car(BASE) == symbol(POWER)) {
		push(cadr(BASE));
		push(caddr(BASE));
		push(EXPO);
		multiply_expand(); // always expand products of exponents
		power();
		return;
	}

	// none of the above

	push_symbol(POWER);
	push(BASE);
	push(EXPO);
	list(3);
}

// BASE = e

void
power_natural_number(void)
{
	double x, y;

	// exp(x + i y) = exp(x) (cos(y) + i sin(y))

	if (isdoublez(EXPO)) {
		if (car(EXPO) == symbol(ADD)) {
			x = cadr(EXPO)->u.d;
			y = cadaddr(EXPO)->u.d;
		} else {
			x = 0.0;
			y = cadr(EXPO)->u.d;
		}
		push_double(exp(x));
		push_double(y);
		cosfunc();
		push(imaginaryunit);
		push_double(y);
		sinfunc();
		multiply();
		add();
		multiply();
		return;
	}

	// e^log(expr) = expr

	if (car(EXPO) == symbol(LOG)) {
		push(cadr(EXPO));
		return;
	}

	if (isdenormalpolar(EXPO)) {
		normalize_polar();
		return;
	}

	push_symbol(POWER);
	push_symbol(EXP1);
	push(EXPO);
	list(3);
}

void
normalize_polar(void)
{
	int h;
	if (car(EXPO) == symbol(ADD)) {
		h = tos;
		p1 = cdr(EXPO);
		while (iscons(p1)) {
			EXPO = car(p1);
			if (isdenormalpolarterm(EXPO))
				normalize_polar_term();
			else {
				push_symbol(POWER);
				push_symbol(EXP1);
				push(EXPO);
				list(3);
			}
			p1 = cdr(p1);
		}
		multiply_factors(tos - h);
	} else
		normalize_polar_term();
}

void
normalize_polar_term(void)
{
	// exp(i pi) = -1

	if (length(EXPO) == 3) {
		push_integer(-1);
		return;
	}

	R = cadr(EXPO); // R = coeff of term

	if (isrational(R))
		normalize_polar_term_rational();
	else
		normalize_polar_term_double();
}

void
normalize_polar_term_rational(void)
{
	int n;

	// R = R mod 2

	push(R);
	push_integer(2);
	modfunc();
	R = pop();

	// convert negative rotation to positive

	if (R->sign == MMINUS) {
		push(R);
		push_integer(2);
		add();
		R = pop();
	}

	push(R);
	push_integer(2);
	multiply();
	floorfunc();
	n = pop_integer(); // number of 90 degree turns

	push(R);
	push_integer(n);
	push_rational(-1, 2);
	multiply();
	add();
	R = pop(); // remainder

	switch (n) {

	case 0:
		if (iszero(R))
			push_integer(1);
		else {
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push(R);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
		}
		break;

	case 1:
		if (iszero(R))
			push(imaginaryunit);
		else {
			push_symbol(MULTIPLY);
			push(imaginaryunit);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push(R);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(3);
		}
		break;

	case 2:
		if (iszero(R))
			push_integer(-1);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push(R);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(3);
		}
		break;

	case 3:
		if (iszero(R)) {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			list(3);
		} else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push(R);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(4);
		}
		break;
	}
}

void
normalize_polar_term_double(void)
{
	double coeff, n, r;

	coeff = R->u.d;

	// coeff = coeff mod 2

	coeff = fmod(coeff, 2.0);

	// convert negative rotation to positive

	if (coeff < 0.0)
		coeff += 2.0;

	n = floor(2.0 * coeff); // number of 90 degree turns

	r = coeff - n / 2.0; // remainder

	switch ((int) n) {

	case 0:
		if (r == 0.0)
			push_integer(1);
		else {
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push_double(r);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
		}
		break;

	case 1:
		if (r == 0.0)
			push(imaginaryunit);
		else {
			push_symbol(MULTIPLY);
			push(imaginaryunit);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push_double(r);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(3);
		}
		break;

	case 2:
		if (r == 0.0)
			push_integer(-1);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push_double(r);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(3);
		}
		break;

	case 3:
		if (r == 0.0) {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			list(3);
		} else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			push_symbol(POWER);
			push_symbol(EXP1);
			push_symbol(MULTIPLY);
			push_double(r);
			push(imaginaryunit);
			push_symbol(PI);
			list(4);
			list(3);
			list(4);
		}
		break;
	}
}

// (a + b)^n -> (a + b) * (a + b) ...

void
power_sum(void)
{
	int h, i, m, n;

	if (expanding == 0 || !isnum(EXPO) || isnegativenumber(EXPO) || isfraction(EXPO) || (isdouble(EXPO) && EXPO->u.d != floor(EXPO->u.d))) {
		push_symbol(POWER);
		push(BASE);
		push(EXPO);
		list(3);
		return;
	}

	push(EXPO);
	n = pop_integer();

	// square the sum first (prevents infinite loop through multiply)

	h = tos;

	p1 = cdr(BASE);

	while (iscons(p1)) {
		p2 = cdr(BASE);
		while (iscons(p2)) {
			push(car(p1));
			push(car(p2));
			multiply();
			p2 = cdr(p2);
		}
		p1 = cdr(p1);
	}

	add_terms(tos - h);

	// continue up to power m

	m = abs(n);

	for (i = 2; i < m; i++) {
		push(BASE);
		multiply();
	}

	if (n < 0) {
		push_symbol(POWER);
		swap();
		push_integer(-1);
		list(3);
	}
}

void
power_minusone(void)
{
	// optimization for i

	if (equalq(EXPO, 1, 2)) {
		push(imaginaryunit);
		return;
	}

	if (isrational(EXPO)) {
		normalize_clock_rational();
		return;
	}

	if (isdouble(EXPO)) {
		normalize_clock_double();
		rect();
		return;
	}

	push_symbol(POWER);
	push_integer(-1);
	push(EXPO);
	list(3);
}

void
normalize_clock_rational(void)
{
	int n;

	// R = EXPO mod 2

	push(EXPO);
	push_integer(2);
	modfunc();
	R = pop();

	// convert negative rotation to positive

	if (R->sign == MMINUS) {
		push(R);
		push_integer(2);
		add();
		R = pop();
	}

	push(R);
	push_integer(2);
	multiply();
	floorfunc();
	n = pop_integer(); // number of 90 degree turns

	push(R);
	push_integer(n);
	push_rational(-1, 2);
	multiply();
	add();
	R = pop(); // remainder

	switch (n) {

	case 0:
		if (iszero(R))
			push_integer(1);
		else {
			push_symbol(POWER);
			push_integer(-1);
			push(R);
			list(3);
		}
		break;

	case 1:
		if (iszero(R))
			push(imaginaryunit);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_integer(-1);
			push(R);
			push_rational(-1, 2);
			add();
			list(3);
			list(3);
		}
		break;

	case 2:
		if (iszero(R))
			push_integer(-1);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_integer(-1);
			push(R);
			list(3);
			list(3);
		}
		break;

	case 3:
		if (iszero(R)) {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			list(3);
		} else {
			push_symbol(POWER);
			push_integer(-1);
			push(R);
			push_rational(-1, 2);
			add();
			list(3);
		}
		break;
	}
}

void
normalize_clock_double(void)
{
	double expo, n, r;

	expo = EXPO->u.d;

	// expo = expo mod 2

	expo = fmod(expo, 2.0);

	// convert negative rotation to positive

	if (expo < 0.0)
		expo += 2.0;

	n = floor(2.0 * expo); // number of 90 degree turns

	r = expo - n / 2.0; // remainder

	switch ((int) n) {

	case 0:
		if (r == 0.0)
			push_integer(1);
		else {
			push_symbol(POWER);
			push_integer(-1);
			push_double(r);
			list(3);
		}
		break;

	case 1:
		if (r == 0.0)
			push(imaginaryunit);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_integer(-1);
			push_double(r - 0.5);
			list(3);
			list(3);
		}
		break;

	case 2:
		if (r == 0.0)
			push_integer(-1);
		else {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push_symbol(POWER);
			push_integer(-1);
			push_double(r);
			list(3);
			list(3);
		}
		break;

	case 3:
		if (r == 0.0) {
			push_symbol(MULTIPLY);
			push_integer(-1);
			push(imaginaryunit);
			list(3);
		} else {
			push_symbol(POWER);
			push_integer(-1);
			push_double(r - 0.5);
			list(3);
		}
		break;
	}
}

// BASE is rectangular complex numerical, EXPO is numerical

void
power_complex_number(void)
{
	int n;

	// prefixform(2+3*i) = (add 2 (multiply 3 (power -1 1/2)))

	// prefixform(1+i) = (add 1 (power -1 1/2))

	// prefixform(3*i) = (multiply 3 (power -1 1/2))

	// prefixform(i) = (power -1 1/2)

	if (car(BASE) == symbol(ADD)) {
		X = cadr(BASE);
		if (caaddr(BASE) == symbol(MULTIPLY))
			Y = cadaddr(BASE);
		else
			Y = one;
	} else if (car(BASE) == symbol(MULTIPLY)) {
		X = zero;
		Y = cadr(BASE);
	} else {
		X = zero;
		Y = one;
	}

	if (isdouble(X) || isdouble(Y) || isdouble(EXPO)) {
		power_complex_double();
		return;
	}

	if (!isinteger(EXPO)) {
		power_complex_rational();
		return;
	}

	if (!issmallinteger(EXPO)) {
		push_symbol(POWER);
		push(BASE);
		push(EXPO);
		list(3);
		return;
	}

	push(EXPO);
	n = pop_integer();

	if (n > 0)
		power_complex_plus(n);
	else if (n < 0)
		power_complex_minus(-n);
	else
		push_integer(1);
}

void
power_complex_plus(int n)
{
	int i;

	PX = X;
	PY = Y;

	for (i = 1; i < n; i++) {

		push(PX);
		push(X);
		multiply();
		push(PY);
		push(Y);
		multiply();
		subtract();

		push(PX);
		push(Y);
		multiply();
		push(PY);
		push(X);
		multiply();
		add();

		PY = pop();
		PX = pop();
	}

	// X + i*Y

	push(PX);
	push(imaginaryunit);
	push(PY);
	multiply();
	add();
}

//
//               /        \  n
//         -n   |  X - iY  |
// (X + iY)   = | -------- |
//              |   2   2  |
//               \ X + Y  /

// X and Y are rational numbers

void
power_complex_minus(int n)
{
	int i;

	// R = X^2 + Y^2

	push(X);
	push(X);
	multiply();
	push(Y);
	push(Y);
	multiply();
	add();
	R = pop();

	// X = X / R

	push(X);
	push(R);
	divide();
	X = pop();

	// Y = -Y / R

	push(Y);
	negate();
	push(R);
	divide();
	Y = pop();

	PX = X;
	PY = Y;

	for (i = 1; i < n; i++) {

		push(PX);
		push(X);
		multiply();
		push(PY);
		push(Y);
		multiply();
		subtract();

		push(PX);
		push(Y);
		multiply();
		push(PY);
		push(X);
		multiply();
		add();

		PY = pop();
		PX = pop();
	}

	// X + i*Y

	push(PX);
	push(imaginaryunit);
	push(PY);
	multiply();
	add();
}

void
power_complex_double(void)
{
	double expo, r, theta, x, y;

	push(EXPO);
	expo = pop_double();

	push(X);
	x = pop_double();

	push(Y);
	y = pop_double();

	r = hypot(x, y);
	theta = atan2(y, x);

	r = pow(r, expo);
	theta = expo * theta;

	x = r * cos(theta);
	y = r * sin(theta);

	push_double(x);
	push_double(y);
	push(imaginaryunit);
	multiply();
	add();
}

// X and Y are rational, EXPO is rational and not an integer

void
power_complex_rational(void)
{
	// calculate sqrt(X^2 + Y^2) ^ (1/2 * EXPO)

	push(X);
	push(X);
	multiply();
	push(Y);
	push(Y);
	multiply();
	add();
	push_rational(1, 2);
	push(EXPO);
	multiply();
	power();

	// calculate (-1) ^ (EXPO * arctan(Y, X) / pi)

	push(Y);
	push(X);
	arctan();
	push_symbol(PI);
	divide();
	push(EXPO);
	multiply();
	EXPO = pop();
	power_minusone();

	// result = sqrt(X^2 + Y^2) ^ (1/2 * EXPO) * (-1) ^ (EXPO * arctan(Y, X) / pi)

	multiply();
}

// BASE and EXPO are numbers

void
power_numbers(void)
{
	uint32_t *a, *b;

	if (iszero(EXPO)) {
		push_integer(1); // 0^0 = 1
		return;
	}

	if (iszero(BASE)) {
		if (isnegativenumber(EXPO))
			stop("divide by zero");
		push_integer(0);
		return;
	}

	if (isplusone(BASE)) {
		push_integer(1);
		return;
	}

	if (isplusone(EXPO)) {
		push(BASE);
		return;
	}

	if (isdouble(BASE) || isdouble(EXPO)) {
		power_double();
		return;
	}

	if (isinteger(EXPO)) {
		a = mpow(BASE->u.q.a, EXPO->u.q.a);
		b = mpow(BASE->u.q.b, EXPO->u.q.a);
		if (isnegativenumber(BASE) && (EXPO->u.q.a[0] & 1))
			if (isnegativenumber(EXPO))
				push_bignum(MMINUS, b, a); // reciprocate
			else
				push_bignum(MMINUS, a, b);
		else
			if (isnegativenumber(EXPO))
				push_bignum(MPLUS, b, a); // reciprocate
			else
				push_bignum(MPLUS, a, b);
		return;
	}

	if (isminusone(BASE)) {
		power_minusone();
		return;
	}

	if (isnegativenumber(BASE)) {
		power_minusone();
		push(BASE);
		negate();
		BASE = pop();
		power_rationals();
		multiply();
		return;
	}

	power_rationals();
}

void
power_rationals(void)
{
	int i, j, h, n;
	struct atom **s;
	uint32_t *base_numer, *base_denom;
	uint32_t *expo_numer, *expo_denom;

	base_numer = BASE->u.q.a;
	base_denom = BASE->u.q.b;

	expo_numer = EXPO->u.q.a;
	expo_denom = EXPO->u.q.b;

	h = tos;
	s = stack + h;

	// put factors on stack

	push_symbol(POWER);
	push(BASE);
	push(EXPO);
	list(3);

	factor_factor();

	// normalize factors

	n = tos - h;

	for (i = 0; i < n; i++) {
		p1 = s[i];
		if (car(p1) == symbol(POWER)) {
			BASE = cadr(p1);
			EXPO = caddr(p1);
			power_rationals_nib();
			s[i] = pop(); // trick: fill hole
		}
	}

	// combine numbers (leaves radicals on stack)

	p2 = one;

	n = tos - h;

	for (i = 0; i < n; i++) {
		p1 = s[i];
		if (isnum(p1)) {
			push(p1);
			push(p2);
			multiply();
			p2 = pop();
			for (j = i + 1; j < n; j++)
				s[j - 1] = s[j];
			i--;
			n--;
			tos--;
		}
	}

	// finalize

	n = tos - h;

	if (n == 0 || !isplusone(p2)) {
		push(p2);
		n++;
	}

	if (n == 1)
		return;

	sort_factors(n);
	list(n);
	push_symbol(MULTIPLY);
	swap();
	cons();
}

// BASE is an integer, EXPO is an integer or rational number

void
power_rationals_nib(void)
{
	uint32_t *a, *b, *base, *expo_numer, *expo_denom, *n, *q, *r;

	base = BASE->u.q.a;

	expo_numer = EXPO->u.q.a;
	expo_denom = EXPO->u.q.b;

	// integer power?

	if (isinteger(EXPO)) {
		a = mpow(base, expo_numer);
		b = mint(1);
		if (isnegativenumber(EXPO))
			push_bignum(MPLUS, b, a); // reciprocate
		else
			push_bignum(MPLUS, a, b);
		return;
	}

	// EXPO.a          r
	// ------ == q + ------
	// EXPO.b        EXPO.b

	q = mdiv(expo_numer, expo_denom);
	r = mmod(expo_numer, expo_denom);

	// process q

	if (!MZERO(q)) {
		a = mpow(base, q);
		b = mint(1);
		if (isnegativenumber(EXPO))
			push_bignum(MPLUS, b, a); // reciprocate
		else
			push_bignum(MPLUS, a, b);
	}

	mfree(q);

	// process r

	if (MLENGTH(base) == 1) {
		// BASE is 32 bits or less, hence a prime number, no root
		push_symbol(POWER);
		push(BASE);
		push_bignum(EXPO->sign, r, mcopy(expo_denom));
		list(3);
		return;
	}

	// BASE was too big to factor, try finding root

	n = mroot(base, expo_denom);

	if (n == NULL) {
		// no root
		push_symbol(POWER);
		push(BASE);
		push_bignum(EXPO->sign, r, mcopy(expo_denom));
		list(3);
		return;
	}

	// raise root n to rth power

	a = mpow(n, r);
	b = mint(1);

	mfree(n);
	mfree(r);

	if (isnegativenumber(EXPO))
		push_bignum(MPLUS, b, a); // reciprocate
	else
		push_bignum(MPLUS, a, b);
}

void
power_double(void)
{
	double base, d, expo;

	push(BASE);
	base = pop_double();

	push(EXPO);
	expo = pop_double();

	if (base > 0.0 || expo == floor(expo)) {
		d = pow(base, expo);
		push_double(d);
		return;
	}

	// BASE is negative and EXPO is fractional

	power_minusone();

	if (base == -1.0)
		return;

	d = pow(-base, expo);
	push_double(d);

	multiply();
}

void
sqrtfunc(void)
{
	push_rational(1, 2);
	power();
}

void
power_tensor(void)
{
	int i, n;

	push(BASE);
	copy_tensor();
	p1 = pop();

	n = p1->u.tensor->nelem;

	for (i = 0; i < n; i++) {
		push(p1->u.tensor->elem[i]);
		push(EXPO);
		power();
		p1->u.tensor->elem[i] = pop();
	}

	push(p1);
}
