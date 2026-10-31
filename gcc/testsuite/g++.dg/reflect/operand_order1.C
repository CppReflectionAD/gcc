// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Operands are reflected in source order, and not simplified.

#include <meta>

using namespace std::meta;

double h (double);

void f (int p, double d, double e, bool a, bool b, int x)
{
  double q0 = d + p;
  double q1 = d * h (e);
  double q2 = 2.0 * d;
  int q3 = x - x;
  bool q4 = !(a || b);
}

consteval info strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}
consteval info init (int i)
{
  return strip (initializer_of (statements_of (body_of (^^f))[i]));
}
consteval info op0 (int i) { return strip (operands_of (init (i))[0]); }
consteval bool names_d (info e)
{
  return is_id_expression (e) && identifier_of (declaration_of (e)) == "d";
}

static_assert (names_d (op0 (0)), "d + p: first operand is p");
static_assert (names_d (op0 (1)), "d * h (e): first operand is the call");
static_assert (is_literal (op0 (2)), "2.0 * d: first operand is d");
static_assert (is_operator_expression (init (3)), "x - x: folded to 0");
static_assert (expression_operator_of (init (4)) == operators::op_exclamation,
	       "!(a || b): reflected as !a && !b");
