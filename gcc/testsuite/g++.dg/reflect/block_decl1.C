// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A block-scope declaration that declares no ordinary variable is a
// declaration statement that isn't a simple declaration, so it has no
// declarators (cpp_reflection_ad#235).

#include <meta>

using namespace std::meta;

struct P { double a, b; };

double f_binding (P p) { auto [a, b] = p; return a + b; }
double f_binding_ref (P &p) { auto &[a, b] = p; return a + b; }
template <typename T> struct Q { T a, b; };
template <typename T> T t_binding (T x) { auto [a, b] = Q<T>{x, x}; return a + b; }
template double t_binding<double> (double);

// Whether FN's body is a declaration statement with no declarators, then a
// return.
consteval bool
declaration_then_return (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2
	  && is_declaration_statement (stmts[0])
	  && !is_expression_statement (stmts[0])
	  && !is_simple_declaration (stmts[0])
	  && declarators_of (stmts[0]).empty ()
	  && initializers_of (stmts[0]).empty ()
	  && is_return_statement (stmts[1]));
}

consteval bool
can_declared_variable_of (info r)
{
  try { declared_variable_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

static_assert (declaration_then_return (^^f_binding));
static_assert (declaration_then_return (^^f_binding_ref));
static_assert (declaration_then_return (^^t_binding<double>));
static_assert (!can_declared_variable_of (statements_of (body_of (^^f_binding))[0]));

// What a binding declares in a range-based for or an if's init-statement is
// unchanged: each statement's kinds, one hex digit per statement, then the
// number of statements.
double f_for (P (&arr)[2]) { double s = 0; for (auto [a, b] : arr) s += a; return s; }
double f_if (P p) { if (auto [a, b] = p; a > 0) return a; return p.b; }

consteval int
kind (info s)
{
  return (is_declaration_statement (s) + 2 * is_expression_statement (s)
	  + 4 * is_compound_statement (s) + 8 * is_return_statement (s));
}

consteval int
kinds (info fn)
{
  int r = 0;
  for (info s : statements_of (body_of (fn)))
    r = r * 16 + kind (s);
  return r * 16 + int (statements_of (body_of (fn)).size ());
}

static_assert (kinds (^^f_for) == 0x1483);
static_assert (kinds (^^f_if) == 0x482);
