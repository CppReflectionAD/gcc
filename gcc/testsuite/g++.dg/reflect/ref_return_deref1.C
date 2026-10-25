// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A call to a function returning `const T &`, or a use of a reference, is a
// conversion of the call or the reference, not a unary `*` applied to it.

#include <algorithm>
#include <meta>

using namespace std::meta;

double f_max (double x, double y) { double r = std::max (x, y); return r; }
double f_min (double x, double y) { double r = std::min (x, y); return r; }
double f_ref (const double &p) { double r = p; return r; }
double f_ptr (const double *q) { double r = *q; return r; }

consteval info
strip (info e)
{
  while (is_cast (e))
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

static_assert (is_function_call (init (^^f_max)));
static_assert (is_function_call (init (^^f_min)));
static_assert (is_variable (init (^^f_ref)));
static_assert (!is_unary_operator (init (^^f_ref)));

// A `*` in the source is still a unary operator.
static_assert (is_unary_operator (init (^^f_ptr)));
static_assert (operator_of (init (^^f_ptr)) == operators::op_star);
