// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A prvalue of non-class type bound to a reference parameter is the operand
// of the binding's conversion, without the temporary it initializes.

#include <algorithm>
#include <cmath>
#include <meta>

using namespace std::meta;

struct S { double v; S (double d) : v (d) {} };

double take (const double &p) { return p; }
double take_s (const S &s) { return s.v; }

double f_diff (double x, double y) { double r = take (x - y); return r; }
double f_neg (double x) { double r = take (-x); return r; }
double f_call (double x) { double r = take (std::exp (x)); return r; }
double f_cond (double x) { double r = take (x > 0 ? 1.0 : x); return r; }
double f_lit () { double r = take (0.5); return r; }
double f_lvalue (double x) { double r = take (x); return r; }
double f_max (double x, double y) { double r = std::max (x - y, 0.5); return r; }
double f_class (double x, double y) { double r = take_s (S (x - y)); return r; }

consteval info
strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

// The initializer of the first local, without its conversions.
consteval info
init (info fn)
{
  info s = statements_of (body_of (fn))[0];
  return strip (initializer_of (declared_variable_of (s)));
}

// Argument I of the call that initializes the first local of FN, as given:
// the conversion that binds the reference.
consteval info
arg (info fn, int i)
{
  return operands_of (init (fn))[i];
}

// The binding's operand is the prvalue itself.
static_assert (is_conversion (arg (^^f_diff, 0)));
static_assert (is_binary_operator (operands_of (arg (^^f_diff, 0))[0]));
static_assert (expression_operator_of (operands_of (arg (^^f_diff, 0))[0])
	       == operators::op_minus);
static_assert (is_id_expression (strip (operands_of (operands_of (arg (^^f_diff, 0))[0])[0])));
static_assert (is_id_expression (strip (operands_of (operands_of (arg (^^f_diff, 0))[0])[1])));

static_assert (is_unary_operator (operands_of (arg (^^f_neg, 0))[0]));
static_assert (expression_operator_of (operands_of (arg (^^f_neg, 0))[0])
	       == operators::op_minus);

static_assert (is_function_call (operands_of (arg (^^f_call, 0))[0]));
static_assert (is_id_expression (strip (operands_of (operands_of (arg (^^f_call, 0))[0])[0])));

static_assert (is_conditional_operator (operands_of (arg (^^f_cond, 0))[0]));

static_assert (constant_of (strip (arg (^^f_lit, 0))) == reflect_constant (0.5));

// An lvalue argument is unchanged.
static_assert (is_id_expression (strip (arg (^^f_lvalue, 0))));

// The std::max case that cpp_reflection_ad differentiates.
static_assert (is_binary_operator (strip (arg (^^f_max, 0))));
static_assert (constant_of (strip (arg (^^f_max, 1))) == reflect_constant (0.5));

// A class prvalue is a construct, and keeps it.
static_assert (is_construct (operands_of (arg (^^f_class, 0))[0]));
static_assert (is_binary_operator (strip (arg (^^f_class, 0))));
