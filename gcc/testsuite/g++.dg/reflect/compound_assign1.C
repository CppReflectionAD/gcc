// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A compound assignment `a op= b' is reflected as written: its operator is
// `op=' and its operands are `a' and `b', although it is built as
// `a = a op b'.

#include <meta>

using namespace std::meta;

struct P { double x, y; };
double g ();
double &r ();

void add (double &a, double b) { a += b; }
void sub (double &a, double b) { a -= b; }
void mul (double &a, double b) { a *= b; }
void quot (double &a, double b) { a /= b; }
void rem (int &a, int b) { a %= b; }
void shl (int &a, int b) { a <<= b; }
void shr (int &a, int b) { a >>= b; }
void band (int &a, int b) { a &= b; }
void bor (int &a, int b) { a |= b; }
void bxor (int &a, int b) { a ^= b; }
void plain (double &a, double b) { a = a + b; }
void narrow (int &a, double b) { a += b; }
void promoted (short &a, short b) { a += b; }
void call (double &a) { a += g (); }
void member (P &p) { p.x += p.y * 0.5; }
void folded (double &a) { a += 2.0 * 3.0; }
void pointer (double *&p, int n) { p += n; }
void pointer_sub (double *&p, int n) { p -= n; }
void lcall (double b) { r () += b; }
void lcall_plain (double b) { r () = b; }
void lsub (double *a, int i, double b) { a[i++] += b; }
void lsub_plain (double *a, int i, double b) { a[i++] = b; }
void nested (double &c, double &a, double b) { c = (a += b); }
void init (double &a, double b) { double c = (a *= b); }
template <typename T> void tmpl (T &a, T b) { a -= b; }
template void tmpl (double &, double);

consteval info
stmt (info fn)
{
  return statements_of (body_of (fn))[0];
}

consteval info
expr (info fn)
{
  return expression_of (stmt (fn));
}

consteval operators
op (info fn)
{
  return expression_operator_of (expr (fn));
}

consteval info
strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

consteval bool
names (info e, std::string_view name)
{
  e = strip (e);
  return (is_id_expression (e)
	  && identifier_of (declaration_of (e)) == name);
}

consteval bool
as_written (info fn, std::string_view a, std::string_view b)
{
  auto ops = operands_of (expr (fn));
  return ops.size () == 2 && names (ops[0], a) && names (ops[1], b);
}

static_assert (op (^^add) == operators::op_plus_equals);
static_assert (op (^^sub) == operators::op_minus_equals);
static_assert (op (^^mul) == operators::op_star_equals);
static_assert (op (^^quot) == operators::op_slash_equals);
static_assert (op (^^rem) == operators::op_percent_equals);
static_assert (op (^^shl) == operators::op_less_less_equals);
static_assert (op (^^shr) == operators::op_greater_greater_equals);
static_assert (op (^^band) == operators::op_ampersand_equals);
static_assert (op (^^bor) == operators::op_pipe_equals);
static_assert (op (^^bxor) == operators::op_caret_equals);

static_assert (as_written (^^add, "a", "b"));
static_assert (as_written (^^sub, "a", "b"));
static_assert (as_written (^^quot, "a", "b"));
static_assert (as_written (^^rem, "a", "b"));
static_assert (as_written (^^shr, "a", "b"));
static_assert (as_written (^^bxor, "a", "b"));

// `a = a + b' is an assignment of `a + b'.
static_assert (op (^^plain) == operators::op_equals);
static_assert (expression_operator_of (operands_of (expr (^^plain))[1])
	       == operators::op_plus);

// The operation is done in another type, then converted back.
static_assert (op (^^narrow) == operators::op_plus_equals);
static_assert (as_written (^^narrow, "a", "b"));
static_assert (op (^^promoted) == operators::op_plus_equals);
static_assert (as_written (^^promoted, "a", "b"));

// `g ()' is evaluated before `a' is read, into a temporary.
static_assert (op (^^call) == operators::op_plus_equals);
static_assert (is_function_call (strip (operands_of (expr (^^call))[1])));

// P4395R0 §2.5.
static_assert (op (^^member) == operators::op_plus_equals);
static_assert (expression_operator_of (strip (operands_of (expr (^^member))[1]))
	       == operators::op_star);

// Folding `2.0 * 3.0' to `6.0' rebuilds the assignment.
static_assert (op (^^folded) == operators::op_plus_equals);
static_assert (operands_of (expr (^^folded)).size () == 2);

static_assert (op (^^pointer) == operators::op_plus_equals);
static_assert (op (^^pointer_sub) == operators::op_minus_equals);

// A left operand with side effects is evaluated once, but it is still the
// operand as written, as in a simple assignment.
consteval bool
same_lhs (info compound, info simple)
{
  info a = strip (operands_of (expr (compound))[0]);
  info b = strip (operands_of (expr (simple))[0]);
  return (is_function_call (a) == is_function_call (b)
	  && is_operator_expression (a) == is_operator_expression (b)
	  && (!is_operator_expression (a)
	      || expression_operator_of (a) == expression_operator_of (b)));
}
static_assert (op (^^lcall) == operators::op_plus_equals);
static_assert (is_function_call (strip (operands_of (expr (^^lcall))[0])));
static_assert (names (operands_of (expr (^^lcall))[1], "b"));
static_assert (same_lhs (^^lcall, ^^lcall_plain));
static_assert (op (^^lsub) == operators::op_plus_equals);
static_assert (names (operands_of (expr (^^lsub))[1], "b"));
static_assert (same_lhs (^^lsub, ^^lsub_plain));

static_assert (op (^^nested) == operators::op_equals);
static_assert (expression_operator_of (strip (operands_of (expr (^^nested))[1]))
	       == operators::op_plus_equals);

static_assert (expression_operator_of
		 (strip (initializer_of (declared_variable_of (stmt (^^init)))))
	       == operators::op_star_equals);

static_assert (op (^^tmpl<double>) == operators::op_minus_equals);
static_assert (as_written (^^tmpl<double>, "a", "b"));
