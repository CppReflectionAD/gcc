// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// An argument bound to a reference parameter is a conversion of the
// argument, not of a unary `&` applied to it.

#include <algorithm>
#include <meta>

using namespace std::meta;

double take (const double &p) { return p; }
const double *addr (const double *q) { return q; }

double f_max (double x, double y) { double r = std::max (x, y); return r; }
double f_take (double x) { double r = take (x); return r; }
double f_ptr (double x) { double r = *addr (&x); return r; }

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

// Argument I of call E.
consteval info
arg (info e, int i)
{
  return operands_of (e)[i];
}

static_assert (is_function_call (init (^^f_max)));
static_assert (is_id_expression (strip (arg (init (^^f_max), 0))));
static_assert (is_id_expression (strip (arg (init (^^f_max), 1))));
static_assert (is_id_expression (strip (arg (init (^^f_take), 0))));

// A `&` in the source is still a unary operator.
static_assert (is_unary_operator (strip (arg (strip (operands_of (init (^^f_ptr))[0]), 0))));
static_assert (expression_operator_of (strip (arg (strip (operands_of (init (^^f_ptr))[0]), 0)))
	       == operators::op_ampersand);
