// Run 'make' in 'eigenmath/tools' directory to update this file
void eval_abs(struct atom *p1);
void absfunc(void);
void eval_add(struct atom *p1);
void add(void);
void add_terms(int n);
void flatten_terms(int h);
struct atom * combine_tensors(int h);
void add_tensors(void);
void combine_terms(int h);
int combine_terms_nib(int i, int j);
void sort_terms(int n);
int sort_terms_func(const void *q1, const void *q2);
int cmp_terms(struct atom *p1, struct atom *p2);
int simplify_terms(int h);
int isradicalterm(struct atom *p);
int is_imaginary_term(struct atom *p);
void add_numbers(struct atom *p1, struct atom *p2);
void add_rationals(struct atom *p1, struct atom *p2);
void add_integers(struct atom *p1, struct atom *p2);
void subtract(void);
void eval_adj(struct atom *p1);
void adj(void);
struct atom * alloc_atom(void);
void alloc_block(void);
struct atom * alloc_vector(int nrow);
struct atom * alloc_matrix(int nrow, int ncol);
struct atom * alloc_tensor(int nelem);
void eval_arccos(struct atom *p1);
void arccos(void);
void eval_arccosh(struct atom *p1);
void arccosh(void);
void eval_arcsin(struct atom *p1);
void arcsin(void);
void eval_arcsinh(struct atom *p1);
void arcsinh(void);
void eval_arctan(struct atom *p1);
void arctan(void);
void arctan_numbers(struct atom *X, struct atom *Y);
void eval_arctanh(struct atom *p1);
void arctanh(void);
void eval_arg(struct atom *p1);
void arg(void);
void arg1(void);
void init_bignums(void);
void push_integer(int n);
void push_rational(int a, int b);
void push_bignum(int sign, uint32_t *a, uint32_t *b);
int pop_integer(void);
void push_double(double d);
double pop_double(void);
int isequaln(struct atom *p, int n);
int isequalq(struct atom *p, int a, int b);
int cmpfunc(void);
int cmp_numbers(struct atom *p1, struct atom *p2);
int cmp_rationals(struct atom *a, struct atom *b);
double convert_rational_to_double(struct atom *p);
void convert_double_to_rational(double d);
void best_rational_approximation(double x);
void bignum_scan_integer(char *s);
void bignum_float(void);
void bignum_factorial(int n);
uint32_t * bignum_factorial_nib(int n);
void msetbit(uint32_t *x, uint32_t k);
void mclrbit(uint32_t *x, uint32_t k);
void mshiftright(uint32_t *a);
uint32_t * mscan(char *s);
char * mstr(uint32_t *u);
int mdivby1billion(uint32_t *u);
uint32_t * madd(uint32_t *u, uint32_t *v);
uint32_t * msub(uint32_t *u, uint32_t *v);
uint32_t * mmul(uint32_t *u, uint32_t *v);
uint32_t * mdiv(uint32_t *u, uint32_t *v);
uint32_t * mmod(uint32_t *u, uint32_t *v);
uint32_t * mpow(uint32_t *u, uint32_t *v);
void mshr(uint32_t *u);
int mcmp(uint32_t *u, uint32_t *v);
int meq(uint32_t *u, uint32_t *v);
uint32_t * mint(uint32_t n);
uint32_t * mnew(int n);
void mfree(uint32_t *u);
uint32_t * mcopy(uint32_t *u);
void mnorm(uint32_t *u);
uint32_t * mgcd(uint32_t *u, uint32_t *v);
uint32_t * mmodpow(uint32_t *x, uint32_t *n, uint32_t *m);
uint32_t * mroot(uint32_t *a, uint32_t *n);
int mprime(uint32_t *n);
int mprimef(uint32_t *n, uint32_t *q, int k);
void eval_ceiling(struct atom *p1);
void ceilingfunc(void);
void eval_circexp(struct atom *p1);
void circexp(void);
void circexp_subst(void);
void eval_exptan(struct atom *p1);
void exptan(void);
void eval_expcosh(struct atom *p1);
void expcosh(void);
void eval_expsinh(struct atom *p1);
void expsinh(void);
void eval_exptanh(struct atom *p1);
void exptanh(void);
void eval_clock(struct atom *p1);
void clockfunc(void);
void eval_cofactor(struct atom *p1);
void eval_conj(struct atom *p1);
void conjfunc(void);
void conjfunc_subst(void);
void eval_contract(struct atom *p1);
void contract(void);
void list(int n);
void cons(void);
int length(struct atom *p);
int find(struct atom *p, struct atom *q);
int complexity(struct atom *p);
void sort(int n);
int sort_func(const void *p1, const void *p2);
int lessp(struct atom *p1, struct atom *p2);
int cmp_expr(struct atom *p1, struct atom *p2);
int sign(int n);
int iszero(struct atom *p);
int isplusone(struct atom *p);
int isminusone(struct atom *p);
int isinteger(struct atom *p);
int isinteger1(struct atom *p);
int isfraction(struct atom *p);
int isposint(struct atom *p);
int iseveninteger(struct atom *p);
int isradical(struct atom *p);
int isnegativeterm(struct atom *p);
int isnegativenumber(struct atom *p);
int iscomplexnumber(struct atom *p);
int isimaginarynumber(struct atom *p);
int isimaginaryunit(struct atom *p);
int isoneoversqrttwo(struct atom *p);
int isminusoneoversqrttwo(struct atom *p);
int isdoublez(struct atom *p);
int ispoly(struct atom *p, struct atom *x);
int ispoly_expr(struct atom *p, struct atom *x);
int ispoly_term(struct atom *p, struct atom *x);
int ispoly_factor(struct atom *p, struct atom *x);
int find_denominator(struct atom *p);
int count_denominators(struct atom *p);
int count_numerators(struct atom *p);
int isdenominator(struct atom *p);
int isnumerator(struct atom *p);
int isdoublesomewhere(struct atom *p);
int isusersymbolsomewhere(struct atom *p);
int isdenormalpolar(struct atom *p);
int isdenormalpolarterm(struct atom *p);
int issquarematrix(struct atom *p);
int issmallinteger(struct atom *p);
void eval_cos(struct atom *p1);
void cosfunc(void);
void cosfunc_sum(struct atom *p1);
void eval_cosh(struct atom *p1);
void coshfunc(void);
void eval_defint(struct atom *p1);
void eval_denominator(struct atom *p1);
void denominator(void);
void eval_derivative(struct atom *p1);
void derivative(void);
void d_scalar_scalar(struct atom *F, struct atom *X);
void dsum(struct atom *p1, struct atom *p2);
void dproduct(struct atom *p1, struct atom *p2);
void dpower(struct atom *p1, struct atom *p2);
void dlog(struct atom *p1, struct atom *p2);
void dd(struct atom *p1, struct atom *p2);
void dfunction(struct atom *p1, struct atom *p2);
void dsin(struct atom *p1, struct atom *p2);
void dcos(struct atom *p1, struct atom *p2);
void dtan(struct atom *p1, struct atom *p2);
void darcsin(struct atom *p1, struct atom *p2);
void darccos(struct atom *p1, struct atom *p2);
void darctan(struct atom *p1, struct atom *p2);
void dsinh(struct atom *p1, struct atom *p2);
void dcosh(struct atom *p1, struct atom *p2);
void dtanh(struct atom *p1, struct atom *p2);
void darcsinh(struct atom *p1, struct atom *p2);
void darccosh(struct atom *p1, struct atom *p2);
void darctanh(struct atom *p1, struct atom *p2);
void derf(struct atom *p1, struct atom *p2);
void derfc(struct atom *p1, struct atom *p2);
void derivative_of_integral(struct atom *p1, struct atom *p2);
void d_tensor_tensor(struct atom *p1, struct atom *p2);
void d_scalar_tensor(struct atom *p1, struct atom *p2);
void d_tensor_scalar(struct atom *p1, struct atom *p2);
void eval_det(struct atom *p1);
void det(void);
void eval_eigenvec(struct atom *p1);
void eigen(struct atom *p1);
int step(void);
void step2(int p, int q);
int equal(struct atom *p1, struct atom *p2);
void eval_erf(struct atom *p1);
void erffunc(void);
void eval_erfc(struct atom *p1);
void erfcfunc(void);
void eval(void);
void eval_nib(void);
void eval_user_symbol(struct atom *p1);
void eval_binding(struct atom *p1);
void eval_clear(struct atom *p1);
void eval_do(struct atom *p1);
void eval_eval(struct atom *p1);
void eval_nil(struct atom *p1);
void eval_number(struct atom *p1);
void eval_quote(struct atom *p1);
void eval_sqrt(struct atom *p1);
void eval_stop(struct atom *p1);
void eval_subst(struct atom *p1);
void eval_exp(struct atom *p1);
void expfunc(void);
void eval_expcos(struct atom *p1);
void expcos(void);
void eval_expsin(struct atom *p1);
void expsin(void);
void eval_factor(struct atom *p1);
void factorpoly(void);
void factorpoly_coeffs(struct atom *P, struct atom *X);
int factorpoly_root(int h);
void factorpoly_divide(int h, struct atom *A);
void factorpoly_eval(int h, int n, struct atom *X);
void factorpoly_push_divisors(int a);
void factorpoly_gen(int h, int k);
void factorpoly_factor_small_number(int n);
void factor_factor(void);
void factor_bignum(uint32_t *a, struct atom *EXPO);
void eval_factorial(struct atom *p1);
void factorial(void);
void eval_filter(struct atom *p1);
void filter(void);
void filter_sum(struct atom *p1, struct atom *p2);
void filter_tensor(struct atom *p1, struct atom *p2);
void eval_float(struct atom *p1);
void floatfunc(void);
void floatfunc_subst(void);
void eval_floor(struct atom *p1);
void floorfunc(void);
void fmt(void);
void fmt_args(struct atom *p);
void fmt_base(struct atom *p);
void fmt_denominators(struct atom *p);
void fmt_double(struct atom *p);
void fmt_exponent(struct atom *p);
void fmt_expr(struct atom *p);
void fmt_expr_nib(struct atom *p);
void fmt_factor(struct atom *p);
void fmt_frac(struct atom *p);
void fmt_function(struct atom *p);
void fmt_indices(struct atom *p);
void fmt_infix_operator(int c);
void fmt_list(struct atom *p);
void fmt_matrix(struct atom *p, int d, int k);
void fmt_numerators(struct atom *p);
void fmt_numeric_exponent(struct atom *p);
void fmt_power(struct atom *p);
void fmt_rational(struct atom *p);
void fmt_reciprocal(struct atom *p);
void fmt_roman_char(int c);
void fmt_roman_string(char *s);
void fmt_space(void);
void fmt_string(struct atom *p);
void fmt_subexpr(struct atom *p);
void fmt_symbol(struct atom *p);
int fmt_symbol_fragment(char *s, int k);
void fmt_table(int x, int y, struct atom *p);
void fmt_tensor(struct atom *p);
void fmt_term(struct atom *p);
void fmt_term_nib(struct atom *p);
void fmt_update_fraction(void);
void fmt_update_list(int t);
void fmt_update_subexpr(void);
void fmt_update_subscript(void);
void fmt_update_superscript(void);
void fmt_update_table(int n, int m);
void fmt_vector(struct atom *p);
void fmt_draw(int x, int y, struct atom *p);
void fmt_draw_char(int x, int y, int c);
void fmt_draw_delims(int x, int y, int h, int d, int w);
void fmt_draw_ldelim(int x, int y, int h, int d);
void fmt_draw_rdelim(int x, int y, int h, int d);
void fmt_draw_table(int x, int y, struct atom *p);
void writec(int c);
void eval_for(struct atom *p1);
void gc(void);
void untag(struct atom *p);
void eval_hadamard(struct atom *p1);
void hadamard(void);
void eval_imag(struct atom *p1);
void imag(void);
void eval_index(struct atom *p1);
void indexfunc(struct atom *T, int h);
void eval_infixform(struct atom *p1);
void print_infixform(struct atom *p);
void infixform_subexpr(struct atom *p);
void infixform_expr(struct atom *p);
void infixform_expr_nib(struct atom *p);
void infixform_term(struct atom *p);
void infixform_term_nib(struct atom *p);
void infixform_numerators(struct atom *p);
void infixform_denominators(struct atom *p);
void infixform_factor(struct atom *p);
void infixform_power(struct atom *p);
void infixform_reciprocal(struct atom *p);
void infixform_factorial(struct atom *p);
void infixform_index(struct atom *p);
void infixform_arglist(struct atom *p);
void infixform_rational(struct atom *p);
void infixform_double(struct atom *p);
void infixform_base(struct atom *p);
void infixform_numeric_base(struct atom *p);
void infixform_numeric_exponent(struct atom *p);
void infixform_tensor(struct atom *p);
void infixform_tensor_nib(struct atom *p, int d, int k);
void eval_inner(struct atom *p1);
void inner(void);
void eval_integral(struct atom *p1);
void integral(void);
void integral_of_form(struct atom *F, struct atom *X);
void integral_lookup(int h, struct atom *F);
int integral_classify(struct atom *p);
int find_integral(int h, char **s, struct atom *F);
int find_integral_nib(int h, struct atom *F, struct atom *I, struct atom *C);
void decomp(void);
void decomp_sum(struct atom *p1, struct atom *p2);
void decomp_product(struct atom *p1, struct atom *p2);
void collect_coeffs(void);
int collect_coeffs_sort_func(const void *q1, const void *q2);
void partition_integrand(void);
void eval_inv(struct atom *p1);
void inv(void);
void eval_kronecker(struct atom *p1);
void kronecker(void);
void eval_latex(struct atom *p1);
void latex(void);
void latex_expr(struct atom *p);
void latex_term(struct atom *p);
void latex_numerators(struct atom *p);
void latex_denominators(struct atom *p);
void latex_factor(struct atom *p);
void latex_number(struct atom *p);
void latex_rational(struct atom *p);
void latex_double(struct atom *p);
void latex_power(struct atom *p);
void latex_base(struct atom *p);
void latex_exponent(struct atom *p);
void latex_imaginary(struct atom *p);
void latex_function(struct atom *p);
void latex_arglist(struct atom *p);
void latex_subexpr(struct atom *p);
void latex_symbol(struct atom *p);
int latex_symbol_scan(char *s);
void latex_symbol_shipout(char *s, int n);
void latex_tensor(struct atom *p);
void latex_tensor_matrix(struct tensor *t, int d, int *k);
void latex_string(struct atom *p);
void eval_log(struct atom *p1);
void logfunc(void);
void eval_mag(struct atom *p1);
void mag(void);
void mag1(void);
int main(int argc, char *argv[]);
void run_stdin(void);
void prompt(void);
void echo_stdin(void);
void run_infile(void);
void printbuf(char *s, int color);
void display(void);
void begin_document(void);
void end_document(void);
void begin_latex(void);
void end_latex(void);
void begin_mathml(void);
void end_mathml(void);
void begin_mathjax(void);
void end_mathjax(void);
void eval_draw(struct atom *p1);
void eval_exit(struct atom *p1);
void eval_mathjax(struct atom *p1);
void mathjax(void);
void eval_mathml(struct atom *p1);
void mathml(void);
void mml_expr(struct atom *p);
void mml_term(struct atom *p);
void mml_numerators(struct atom *p);
void mml_denominators(struct atom *p);
void mml_factor(struct atom *p);
void mml_number(struct atom *p);
void mml_rational(struct atom *p);
void mml_double(struct atom *p);
void mml_power(struct atom *p);
void mml_base(struct atom *p);
void mml_exponent(struct atom *p);
void mml_imaginary(struct atom *p);
void mml_function(struct atom *p);
void mml_arglist(struct atom *p);
void mml_subexpr(struct atom *p);
void mml_symbol(struct atom *p);
int mml_symbol_scan(char *s);
void mml_symbol_shipout(char *s, int n);
void mml_tensor(struct atom *p);
void mml_matrix(struct tensor *t, int d, int *k);
void mml_string(struct atom *p, int mathmode);
void mml_mi(char *s);
void mml_mn(char *s);
void mml_mo(char *s);
void eval_minor(struct atom *p1);
void eval_minormatrix(struct atom *p1);
void minormatrix(int row, int col);
void eval_mod(struct atom *p1);
void modfunc(void);
void mod_rationals(struct atom *p1, struct atom *p2);
void mod_integers(struct atom *p1, struct atom *p2);
void eval_multiply(struct atom *p1);
void multiply(void);
void multiply_factors(int n);
void flatten_factors(int h);
struct atom * multiply_tensor_factors(int h);
void multiply_scalar_factors(int h);
struct atom * combine_numerical_factors(int h, struct atom *COEF);
void combine_factors(int h);
int combine_factors_nib(int i, int j);
void sort_factors_provisional(int h);
int sort_factors_provisional_func(const void *q1, const void *q2);
int cmp_factors_provisional(struct atom *p1, struct atom *p2);
void factor_factors_maybe(int h);
void normalize_power_factors(int h);
void expand_sum_factors(int h);
void sort_factors(int n);
int sort_factors_func(const void *q1, const void *q2);
int cmp_factors(struct atom *p1, struct atom *p2);
int order_factor(struct atom *p);
void multiply_numbers(struct atom *p1, struct atom *p2);
void multiply_rationals(struct atom *p1, struct atom *p2);
struct atom * reduce_radical_factors(int h, struct atom *COEF);
int any_radical_factors(int h);
struct atom * reduce_radical_double(int h, struct atom *COEF);
struct atom * reduce_radical_rational(int h, struct atom *COEF);
void multiply_expand(void);
void multiply_noexpand(void);
void multiply_factors_noexpand(int n);
void negate(void);
void negate_noexpand(void);
void reciprocate(void);
void divide(void);
void eval_noexpand(struct atom *p1);
void eval_nroots(struct atom *p1);
void nroots(void);
void monic(int n);
void findroot(int n);
void compute_fa(int n);
void nroots_divpoly(int n);
void eval_numerator(struct atom *p1);
void numerator(void);
void eval_outer(struct atom *p1);
void outer(void);
void eval_polar(struct atom *p1);
void polar(void);
void eval_power(struct atom *p1);
void power(void);
void power_sum(struct atom *BASE, struct atom *EXPO);
void sqrtfunc(void);
void power_tensor(struct atom *BASE, struct atom *EXPO);
void power_complex_number(struct atom *BASE, struct atom *EXPO);
void power_complex_plus(struct atom *X, struct atom *Y, int n);
void power_complex_minus(struct atom *X, struct atom *Y, int n);
void power_complex_double(struct atom *X, struct atom *Y, struct atom *EXPO);
void power_complex_rational(struct atom *X, struct atom *Y, struct atom *EXPO);
void power_minusone(struct atom *EXPO);
void normalize_clock_rational(struct atom *EXPO);
void normalize_clock_double(struct atom *EXPO);
void power_natural_number(struct atom *EXPO);
void normalize_polar(struct atom *EXPO);
void normalize_polar_term(struct atom *EXPO);
void normalize_polar_term_rational(struct atom *R);
void normalize_polar_term_double(struct atom *R);
void power_numbers(struct atom *BASE, struct atom *EXPO);
void power_numbers_factor(struct atom *BASE, struct atom *EXPO);
void power_double(struct atom *BASE, struct atom *EXPO);
void eval_prefixform(struct atom *p1);
void print_prefixform(struct atom *p);
void prefixform(struct atom *p);
void eval_print(struct atom *p1);
void print_result(void);
int annotate_result(struct atom *p1, struct atom *p2);
void print_str(char *s);
void print_char(int c);
void eval_product(struct atom *p1);
void eval_quotient(struct atom *p1);
void quotient(void);
void eval_rationalize(struct atom *p1);
void rationalize(void);
void eval_real(struct atom *p1);
void real(void);
void eval_rect(struct atom *p1);
void rect(void);
void eval_roots(struct atom *p1);
void roots(void);
void eval_rotate(struct atom *p1);
void rotate_h(struct atom *PSI, uint32_t c, int n);
void rotate_p(struct atom *PSI, struct atom *PHASE, uint32_t c, int n);
void rotate_w(struct atom *PSI, uint32_t c, int m, int n);
void rotate_x(struct atom *PSI, uint32_t c, int n);
void rotate_y(struct atom *PSI, uint32_t c, int n);
void rotate_z(struct atom *PSI, uint32_t c, int n);
void rotate_q(struct atom *PSI, int n);
void rotate_v(struct atom *PSI, int n);
void run(char *s);
void init(void);
void prep(void);
char * scan_input(char *s);
void eval_and_print_result(void);
void eval_run(struct atom *p1);
void run_file(char *filename);
void trace_input(void);
void print_input_line(void);
void print_scan_line(char *s);
void eval_status(struct atom *p1);
void run_init_script(void);
void stop(char *s);
void kaput(char *s);
char * scan(char *s);
char * scan1(char *s);
char * scan_nib(char *s);
void scan_stmt(void);
void scan_comparison(void);
void scan_expression(void);
int another_factor_pending(void);
void scan_term(void);
void scan_power(void);
void scan_factor(void);
void scan_symbol(void);
void scan_string(void);
void scan_function_call(void);
void scan_subexpr(void);
void get_token_skip_newlines(void);
void get_token(void);
void get_token_nib(void);
void update_token_buf(char *a, char *b);
void scan_error(char *errmsg);
void build_tensor(int h);
void static_negate(void);
void static_reciprocate(void);
void eval_setq(struct atom *p1);
void setq_indexed(struct atom *p1);
void set_component(struct atom *LVAL, struct atom *RVAL, int h);
void setq_usrfunc(struct atom *p1);
void convert_body(struct atom *A);
void eval_sgn(struct atom *p1);
void sgn(void);
void eval_simplify(struct atom *p1);
void simplify(void);
void simplify_pass1(void);
void simplify_pass2(void);
void simplify_pass3(void);
void eval_sin(struct atom *p1);
void sinfunc(void);
void sinfunc_sum(struct atom *p1);
void eval_sinh(struct atom *p1);
void sinhfunc(void);
void push(struct atom *p);
struct atom * pop(void);
void save_symbol(struct atom *p);
void restore_symbol(struct atom *p);
void swap(void);
void push_string(char *s);
void subst(void);
void eval_sum(struct atom *p1);
struct atom * lookup(char *s);
char * printname(struct atom *p);
void set_symbol(struct atom *p, struct atom *b, struct atom *u);
void undo(void);
struct atom * get_binding(struct atom *p);
struct atom * get_usrfunc(struct atom *p);
void init_symbol_table(void);
void clear_symbols(void);
void eval_tan(struct atom *p1);
void tanfunc(void);
void tanfunc_sum(struct atom *p1);
void eval_tanh(struct atom *p1);
void tanhfunc(void);
void eval_taylor(struct atom *p1);
void eval_tensor(struct atom *p1);
void promote_tensor(void);
int compatible_dimensions(struct atom *p, struct atom *q);
int compare_tensors(struct atom *p1, struct atom *p2);
void copy_tensor(void);
void eval_dim(struct atom *p1);
void eval_rank(struct atom *p1);
void eval_unit(struct atom *p1);
void eval_zero(struct atom *p1);
void eval_test(struct atom *p1);
void eval_check(struct atom *p1);
void eval_testeq(struct atom *p1);
int cross_expr(struct atom *p);
int cross_term(struct atom *p);
int cross_factor(struct atom *p);
void cancel_factor(void);
void eval_testge(struct atom *p1);
void eval_testgt(struct atom *p1);
void eval_testle(struct atom *p1);
void eval_testlt(struct atom *p1);
void eval_not(struct atom *p1);
void eval_and(struct atom *p1);
void eval_or(struct atom *p1);
int cmp_args(struct atom *p1);
void evalp(void);
void eval_transpose(struct atom *p1);
void transpose(void);
void eval_user_function(struct atom *p1);
