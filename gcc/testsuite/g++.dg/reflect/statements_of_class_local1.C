// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A local of class type initialized by a call is one declaration statement,
// and its initializer is the call.

#include <meta>

using namespace std::meta;

struct T { double v; };

T make_t (double x) { return {x}; }

double scalar_local (double x) { double a = x * 2; return a; }
double class_local (double x) { T a = make_t (x); return a.v; }

static_assert (statements_of (body_of (^^scalar_local)).size () == 2);
static_assert (statements_of (body_of (^^class_local)).size () == 2);

consteval info
first_initializer (info fn)
{
  return initializer_of (declared_variable_of (statements_of (body_of (fn))[0]));
}

static_assert (is_declaration_statement
	       (statements_of (body_of (^^class_local))[0]));
static_assert (is_function_call (first_initializer (^^class_local)));
