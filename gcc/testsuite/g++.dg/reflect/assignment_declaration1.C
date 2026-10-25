// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// An assignment is not a declaration statement.

#include <meta>

using namespace std::meta;

double f (double x) { double a = x; a = a * 2; return a; }
double g (double x) { double a = x; a += x; return a; }

consteval int
count_declarations (info fn)
{
  int n = 0;
  for (info s : statements_of (body_of (fn)))
    n += is_declaration_statement (s);
  return n;
}

static_assert (statements_of (body_of (^^f)).size () == 3);
static_assert (count_declarations (^^f) == 1);
static_assert (!is_declaration_statement (statements_of (body_of (^^f))[1]));

static_assert (statements_of (body_of (^^g)).size () == 3);
static_assert (count_declarations (^^g) == 1);
static_assert (!is_declaration_statement (statements_of (body_of (^^g))[1]));
