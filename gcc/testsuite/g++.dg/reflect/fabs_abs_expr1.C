// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A call to a built-in function such as std::fabs is a call in the
// reflection of the function body, not the tree it folds to (ABS_EXPR).

#include <cmath>
#include <cstdlib>
#include <meta>
#include <string_view>

using namespace std::meta;

double f_fabs (double x) { double r = std::fabs (x); return r; }
float f_fabsf (float x) { float r = std::fabs (x); return r; }
int f_abs (int x) { int r = std::abs (x); return r; }
// A call that folds to a constant is still folded.
double f_const () { double r = std::fabs (-2.0); return r; }

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

consteval bool
calls (info fn, std::string_view name)
{
  info e = init (fn);
  return (is_function_call (e)
	  && !is_unary_operator (e)
	  && identifier_of (callee_of (e)) == name);
}

static_assert (calls (^^f_fabs, "fabs"));
static_assert (calls (^^f_fabsf, "fabs"));
static_assert (calls (^^f_abs, "abs"));
static_assert (is_literal (init (^^f_const)));
