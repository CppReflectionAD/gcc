// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// An assignment in an initializer is the initializer's expression.

#include <meta>

using namespace std::meta;

double f (double x)
{
  double a = x;
  double b = (a = a * x);
  return a + b;
}

double g (double x)
{
  double a = x;
  double b = (a += x);
  return a + b;
}

static_assert (statements_of (body_of (^^f)).size () == 3);
constexpr info fb = declared_variable_of (statements_of (body_of (^^f))[1]);
static_assert (expression_operator_of (initializer_of (fb))
	       == operators::op_equals);
static_assert (operands_of (initializer_of (fb)).size () == 2);
static_assert (expression_operator_of (operands_of (initializer_of (fb))[1])
	       == operators::op_star);

// GCC reflects a += x as a = a + x.
static_assert (statements_of (body_of (^^g)).size () == 3);
constexpr info gb = declared_variable_of (statements_of (body_of (^^g))[1]);
static_assert (expression_operator_of (initializer_of (gb))
	       == operators::op_equals);
static_assert (expression_operator_of (operands_of (initializer_of (gb))[1])
	       == operators::op_plus);
