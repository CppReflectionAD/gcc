// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Operators are reflected as written wherever they are in a body.

#include <meta>

using namespace std::meta;

double h (double);
struct T { double v; };

double r1 (double d, int p) { return d + p; }
bool r2 (bool a, bool b) { return !(a || b); }

void
g (double d, int p)
{
  double q;
  q = d + p;
  q += d * p;
  h (d + p);
  T s{d + p};
  static double t = d + p;
  const double c = d + p;
}

consteval info strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}
consteval info op (info e, int i) { return strip (operands_of (e)[i]); }
consteval bool names (info e, std::string_view n)
{
  return is_id_expression (e) && identifier_of (declaration_of (e)) == n;
}
consteval operators oper (info e) { return expression_operator_of (e); }
consteval info stmt (int i) { return statements_of (body_of (^^g))[i]; }
consteval info expr (int i) { return strip (expression_of (stmt (i))); }
consteval info init (int i) { return strip (initializers_of (stmt (i))[0]); }
// Whether E is `d + p' or `d * p', as written.
consteval bool d_then_p (info e, operators o)
{
  return (is_operator_expression (e) && oper (e) == o
	  && names (op (e, 0), "d") && names (op (e, 1), "p"));
}

// A return.
static_assert (d_then_p (strip (return_operand_of (statements_of (body_of (^^r1))[0])),
			 operators::op_plus));
static_assert (oper (strip (return_operand_of (statements_of (body_of (^^r2))[0])))
	       == operators::op_exclamation);
// An assignment.
static_assert (d_then_p (op (expr (1), 1), operators::op_plus));
// A compound assignment.
static_assert (d_then_p (op (op (expr (2), 1), 1), operators::op_star));
// A call argument.
static_assert (d_then_p (op (expr (3), 0), operators::op_plus));
// An aggregate initialization.
static_assert (d_then_p (init (4), operators::op_plus));
// A static local.
static_assert (d_then_p (init (5), operators::op_plus));
// A const local.
static_assert (d_then_p (init (6), operators::op_plus));
// A reflection held in a variable: its expression isn't folded.
constexpr info held = init (6);
static_assert (d_then_p (held, operators::op_plus));
