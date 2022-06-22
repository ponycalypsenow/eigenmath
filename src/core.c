#include "defs.h"

struct atom *
alloc(void)
{
	struct atom *p;

	if (free_count == 0)
		alloc_block();

	p = free_list;
	free_list = p->u.next;

	free_count--;
	alloc_count++;

	return p;
}

void
alloc_block(void)
{
	int i;
	struct atom *p;

	if (block_count == MAXBLOCKS)
		kaput("out of memory");

	p = (struct atom *) malloc(BLOCKSIZE * sizeof (struct atom));

	if (p == NULL)
		kaput("malloc");

	mem[block_count++] = p;

	for (i = 0; i < BLOCKSIZE - 1; i++) {
		p[i].k = FREEATOM;
		p[i].u.next = p + i + 1;
	}

	p[i].k = FREEATOM;
	p[i].u.next = NULL;

	free_list = p;
	free_count = BLOCKSIZE;
}

struct atom *
alloc_vector(int nrow)
{
	struct atom *p = alloc_tensor(nrow);
	p->u.tensor->ndim = 1;
	p->u.tensor->dim[0] = nrow;
	return p;
}

struct atom *
alloc_matrix(int nrow, int ncol)
{
	struct atom *p = alloc_tensor(nrow * ncol);
	p->u.tensor->ndim = 2;
	p->u.tensor->dim[0] = nrow;
	p->u.tensor->dim[1] = ncol;
	return p;
}

struct atom *
alloc_tensor(int nelem)
{
	int i;
	struct atom *p;
	p = alloc();
	p->u.tensor = (struct tensor *) malloc(sizeof (struct tensor) + nelem * sizeof (struct atom *));
	if (p->u.tensor == NULL)
		kaput("malloc");
	p->k = TENSOR;
	p->u.tensor->nelem = nelem;
	for (i = 0; i < nelem; i++)
		p->u.tensor->elem[i] = zero;
	tensor_count++;
	return p;
}

// gc can only be called from main run loop

void
gc(void)
{
	int i, j;
	struct atom *p;

	gc_count++;

	// tag everything

	for (i = 0; i < block_count; i++) {
		p = mem[i];
		for (j = 0; j < BLOCKSIZE; j++)
			p[j].tag = 1;
	}

	// untag what's used

	untag(zero);
	untag(one);
	untag(minusone);
	untag(imaginaryunit);

	// symbol table

	for (i = 0; i < 27 * NSYM; i++) {
		untag(symtab[i]);
		untag(binding[i]);
		untag(usrfunc[i]);
	}

	// collect everything that's still tagged

	free_list = NULL;
	free_count = 0;

	for (i = 0; i < block_count; i++) {

		p = mem[i];

		for (j = 0; j < BLOCKSIZE; j++) {

			if (p[j].tag == 0)
				continue;

			// still tagged so it's unused, put on free list

			switch (p[j].k) {
			case KSYM:
				free(p[j].u.ksym.name);
				ksym_count--;
				break;
			case USYM:
				free(p[j].u.usym.name);
				usym_count--;
				break;
			case RATIONAL:
				mfree(p[j].u.q.a);
				mfree(p[j].u.q.b);
				break;
			case STR:
				free(p[j].u.str);
				string_count--;
				break;
			case TENSOR:
				free(p[j].u.tensor);
				tensor_count--;
				break;
			default:
				break; // FREEATOM, CONS, or DOUBLE
			}

			p[j].k = FREEATOM;
			p[j].u.next = free_list;

			free_list = p + j;
			free_count++;
		}
	}
}

void
untag(struct atom *p)
{
	int i;

	if (p == NULL)
		return;

	while (iscons(p)) {
		if (p->tag == 0)
			return;
		p->tag = 0;
		untag(p->u.cons.car);
		p = p->u.cons.cdr;
	}

	if (p->tag == 0)
		return;

	p->tag = 0;

	if (istensor(p))
		for (i = 0; i < p->u.tensor->nelem; i++)
			untag(p->u.tensor->elem[i]);
}

// create a list from n things on the stack

void
list(int n)
{
	int i;
	push_symbol(NIL);
	for (i = 0; i < n; i++)
		cons();
}

void
cons(void)
{
	struct atom *p;
	p = alloc();
	p->k = CONS;
	p->u.cons.cdr = pop();
	p->u.cons.car = pop();
	push(p);
}

int
length(struct atom *p)
{
	int n = 0;
	while (iscons(p)) {
		n++;
		p = cdr(p);
	}
	return n;
}

// returns 1 if expr p contains expr q, otherweise returns 0

int
find(struct atom *p, struct atom *q)
{
	int i;

	if (equal(p, q))
		return 1;

	if (istensor(p)) {
		for (i = 0; i < p->u.tensor->nelem; i++)
			if (find(p->u.tensor->elem[i], q))
				return 1;
		return 0;
	}

	while (iscons(p)) {
		if (find(car(p), q))
			return 1;
		p = cdr(p);
	}

	return 0;
}

int
complexity(struct atom *p)
{
	int n = 1;

	while (iscons(p)) {
		n += complexity(car(p));
		p = cdr(p);
	}

	return n;
}

int
lessp(struct atom *p1, struct atom *p2)
{
	if (cmp_expr(p1, p2) < 0)
		return 1;
	else
		return 0;
}

void
sort(int n)
{
	qsort(stack + tos - n, n, sizeof (struct atom *), sort_func);
}

int
sort_func(const void *p1, const void *p2)
{
	return cmp_expr(*((struct atom **) p1), *((struct atom **) p2));
}

int
cmp_expr(struct atom *p1, struct atom *p2)
{
	int n;

	if (p1 == p2)
		return 0;

	if (p1 == symbol(NIL))
		return -1;

	if (p2 == symbol(NIL))
		return 1;

	if (isnum(p1) && isnum(p2))
		return cmp_numbers(p1, p2);

	if (isnum(p1))
		return -1;

	if (isnum(p2))
		return 1;

	if (isstr(p1) && isstr(p2))
		return sign(strcmp(p1->u.str, p2->u.str));

	if (isstr(p1))
		return -1;

	if (isstr(p2))
		return 1;

	if (issymbol(p1) && issymbol(p2))
		return sign(strcmp(printname(p1), printname(p2)));

	if (issymbol(p1))
		return -1;

	if (issymbol(p2))
		return 1;

	if (istensor(p1) && istensor(p2))
		return compare_tensors(p1, p2);

	if (istensor(p1))
		return -1;

	if (istensor(p2))
		return 1;

	while (iscons(p1) && iscons(p2)) {
		n = cmp_expr(car(p1), car(p2));
		if (n != 0)
			return n;
		p1 = cdr(p1);
		p2 = cdr(p2);
	}

	if (iscons(p2))
		return -1;

	if (iscons(p1))
		return 1;

	return 0;
}

int
sign(int n)
{
	if (n < 0)
		return -1;
	if (n > 0)
		return 1;
	return 0;
}

int
iszero(struct atom *p)
{
	int i;
	if (isrational(p))
		return MZERO(p->u.q.a);
	else if (isdouble(p))
		return p->u.d == 0.0;
	else if (istensor(p)) {
		for (i = 0; i < p->u.tensor->nelem; i++)
			if (!iszero(p->u.tensor->elem[i]))
				return 0;
		return 1;
	} else
		return 0;
}

int
isplusone(struct atom *p)
{
	return isequaln(p, 1);
}

int
isminusone(struct atom *p)
{
	return isequaln(p, -1);
}

int
isinteger(struct atom *p)
{
	return isrational(p) && MEQUAL(p->u.q.b, 1);
}

int
isinteger1(struct atom *p)
{
	return isinteger(p) && isplusone(p);
}

int
isfraction(struct atom *p)
{
	return isrational(p) && !MEQUAL(p->u.q.b, 1);
}

int
isposint(struct atom *p)
{
	return isinteger(p) && !isnegativenumber(p);
}

int
iseveninteger(struct atom *p)
{
	return isinteger(p) && (p->u.q.a[0] & 1) == 0;
}

int
isradical(struct atom *p)
{
	return car(p) == symbol(POWER) && isposint(cadr(p)) && isfraction(caddr(p));
}

int
isnegativeterm(struct atom *p)
{
	return isnegativenumber(p) || (car(p) == symbol(MULTIPLY) && isnegativenumber(cadr(p)));
}

int
isnegativenumber(struct atom *p)
{
	if (isrational(p))
		return p->sign == MMINUS;
	else if (isdouble(p))
		return p->u.d < 0.0;
	else
		return 0;
}

int
iscomplexnumber(struct atom *p)
{
	return isimaginarynumber(p) || (length(p) == 3 && car(p) == symbol(ADD) && isnum(cadr(p)) && isimaginarynumber(caddr(p)));
}

int
isimaginarynumber(struct atom *p)
{
	return isimaginaryunit(p) || (length(p) == 3 && car(p) == symbol(MULTIPLY) && isnum(cadr(p)) && isimaginaryunit(caddr(p)));
}

int
isimaginaryunit(struct atom *p)
{
	return car(p) == symbol(POWER) && isminusone(cadr(p)) && isequalq(caddr(p), 1, 2);
}

// p == 1/sqrt(2) ?

int
isoneoversqrttwo(struct atom *p)
{
	return car(p) == symbol(POWER) && isequaln(cadr(p), 2) && isequalq(caddr(p), -1, 2);
}

// p == -1/sqrt(2) ?

int
isminusoneoversqrttwo(struct atom *p)
{
	return length(p) == 3 && car(p) == symbol(MULTIPLY) && isminusone(cadr(p)) && isoneoversqrttwo(caddr(p));
}

// x + y * (-1)^(1/2) where x and y are double?

int
isdoublez(struct atom *p)
{
	if (car(p) == symbol(ADD)) {

		if (length(p) != 3)
			return 0;

		if (!isdouble(cadr(p))) // x
			return 0;

		p = caddr(p);
	}

	if (car(p) != symbol(MULTIPLY))
		return 0;

	if (length(p) != 3)
		return 0;

	if (!isdouble(cadr(p))) // y
		return 0;

	p = caddr(p);

	if (car(p) != symbol(POWER))
		return 0;

	if (!isminusone(cadr(p)))
		return 0;

	if (!isequalq(caddr(p), 1, 2))
		return 0;

	return 1;
}

int
ispoly(struct atom *p, struct atom *x)
{
	if (find(p, x))
		return ispoly_expr(p, x);
	else
		return 0;
}

int
ispoly_expr(struct atom *p, struct atom *x)
{
	if (car(p) == symbol(ADD)) {
		p = cdr(p);
		while (iscons(p)) {
			if (!ispoly_term(car(p), x))
				return 0;
			p = cdr(p);
		}
		return 1;
	} else
		return ispoly_term(p, x);
}

int
ispoly_term(struct atom *p, struct atom *x)
{
	if (car(p) == symbol(MULTIPLY)) {
		p = cdr(p);
		while (iscons(p)) {
			if (!ispoly_factor(car(p), x))
				return 0;
			p = cdr(p);
		}
		return 1;
	} else
		return ispoly_factor(p, x);
}

int
ispoly_factor(struct atom *p, struct atom *x)
{
	if (equal(p, x))
		return 1;
	if (car(p) == symbol(POWER) && equal(cadr(p), x)) {
		if (isposint(caddr(p)))
			return 1;
		else
			return 0;
	}
	if (find(p, x))
		return 0;
	else
		return 1;
}

int
find_denominator(struct atom *p)
{
	struct atom *q;
	p = cdr(p);
	while (iscons(p)) {
		q = car(p);
		if (car(q) == symbol(POWER) && isnegativenumber(caddr(q)))
			return 1;
		p = cdr(p);
	}
	return 0;
}

int
count_denominators(struct atom *p)
{
	int n = 0;
	p = cdr(p);
	while (iscons(p)) {
		if (isdenominator(car(p)))
			n++;
		p = cdr(p);
	}
	return n;
}

int
count_numerators(struct atom *p)
{
	int n = 0;
	p = cdr(p);
	while (iscons(p)) {
		if (isnumerator(car(p)))
			n++;
		p = cdr(p);
	}
	return n;
}

int
isdenominator(struct atom *p)
{
	if (car(p) == symbol(POWER) && isnegativenumber(caddr(p)))
		return 1;
	else if (isrational(p) && !MEQUAL(p->u.q.b, 1))
		return 1;
	else
		return 0;
}

int
isnumerator(struct atom *p)
{
	if (car(p) == symbol(POWER) && isnegativenumber(caddr(p)))
		return 0;
	else if (isrational(p) && MEQUAL(p->u.q.a, 1))
		return 0;
	else
		return 1;
}

int
isdoublesomewhere(struct atom *p)
{
	if (isdouble(p))
		return 1;

	if (iscons(p)) {
		p = cdr(p);
		while (iscons(p)) {
			if (isdoublesomewhere(car(p)))
				return 1;
			p = cdr(p);
		}
	}

	return 0;
}

int
isusersymbolsomewhere(struct atom *p)
{
	if (isusersymbol(p) && p != symbol(PI) && p != symbol(EXP1))
		return 1;

	if (iscons(p)) {
		p = cdr(p);
		while (iscons(p)) {
			if (isusersymbolsomewhere(car(p)))
				return 1;
			p = cdr(p);
		}
	}

	return 0;
}

int
isdenormalpolar(struct atom *p)
{
	if (car(p) == symbol(ADD)) {
		p = cdr(p);
		while (iscons(p)) {
			if (isdenormalpolarterm(car(p)))
				return 1;
			p = cdr(p);
		}
		return 0;
	}

	return isdenormalpolarterm(p);
}

// returns 1 if term is (coeff * i * pi) and coeff < 0 or coeff >= 1/2

int
isdenormalpolarterm(struct atom *p)
{
	int t;

	if (car(p) != symbol(MULTIPLY))
		return 0;

	if (length(p) == 3 && isimaginaryunit(cadr(p)) && caddr(p) == symbol(PI))
		return 1;

	if (length(p) != 4 || !isnum(cadr(p)) || !isimaginaryunit(caddr(p)) || cadddr(p) != symbol(PI))
		return 0;

	p = cadr(p); // p = coeff of term

	if (isdouble(p))
		return p->u.d < 0.0 || p->u.d >= 0.5;

	push(p);
	push_rational(1, 2);
	t = cmpfunc();

	if (t >= 0)
		return 1; // p >= 1/2

	push(p);
	push_integer(0);
	t = cmpfunc();

	if (t < 0)
		return 1; // p < 0

	return 0;
}

int
issquarematrix(struct atom *p)
{
	return istensor(p) && p->u.tensor->ndim == 2 && p->u.tensor->dim[0] == p->u.tensor->dim[1];
}

int
issmallinteger(struct atom *p)
{
	if (isinteger(p))
		return MLENGTH(p->u.q.a) == 1 && p->u.q.a[0] <= 0x7fffffff;

	if (isdouble(p))
		return p->u.d == floor(p->u.d) && fabs(p->u.d) <= 0x7fffffff;

	return 0;
}
