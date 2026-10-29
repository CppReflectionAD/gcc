// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A declaration with several declarators is one declaration statement, whose
// declarators_of lists every variable and whose initializers_of lists their
// initializers, although GCC declares each variable with a DECL_EXPR of its
// own (cpp_reflection_ad#220).

#include <initializer_list>
#include <meta>
#include <string_view>

using namespace std::meta;

struct C { constexpr C (double x) : v (x) {} double v; };
struct D { D (double x) : v (x) {} ~D (); double v; };
struct T { double v; };

double separate (double x) { const double a = x; const double b = a * a; return a + b; }
double two (double x) { const double a = x, b = a * a; return a + b; }
double three (double x, double y) { const double a = 2, b = 3, c = x * y; return a * x + b * y + c; }
double mixed (double x) { double a = x, *p = &a, c; c = *p; return c; }
double ctor (double x) { C a (x), b{x}; return a.v + b.v; }
double dtor (double x) { D a (x), b = a.v * x; return a.v + b.v; }
double aggr (double x) { T a = {x}, b = {a.v * x}; return a.v + b.v; }
D nrv_first (double x) { D a (x), b (x * x); return a; }
D nrv_second (double x) { D a (x), b (x * x); return b; }
constexpr double cx (double x) { double a = x, b = a * a; return a + b; }
template <typename U> U tmpl (U x) { U a = x, b = a * a; return a + b; }
template double tmpl<double> (double);

// A generic lambda in a template: its declarators are instantiated with a
// different set of local specializations.
template <typename U>
U
lambda (U x)
{
  auto l = [] (auto y) { U a = y, b = a * a; return a + b; };
  U a = x, b = l (a);
  return b;
}
template double lambda<double> (double);

double
in_block (double x)
{
  double s = 0;
  {
    double a = x, b = a * a;
    s = a + b;
  }
  return s;
}

// Whether STMT is one simple declaration of the variables named NAMES, each
// with an initializer, except for those in NO_INIT.
consteval bool
declares (info stmt, std::initializer_list<std::string_view> names,
	  std::initializer_list<std::string_view> no_init = {})
{
  if (!is_declaration_statement (stmt) || !is_simple_declaration (stmt)
      || is_expression_statement (stmt))
    return false;
  auto vars = declarators_of (stmt);
  auto inits = initializers_of (stmt);
  if (vars.size () != names.size () || inits.size () != names.size ())
    return false;
  std::size_t i = 0;
  for (std::string_view name : names)
    {
      if (identifier_of (vars[i]) != name)
	return false;
      bool initialized = true;
      for (std::string_view n : no_init)
	if (n == name)
	  initialized = false;
      if ((inits[i] != info{}) != initialized
	  || initializer_of (vars[i]) != inits[i])
	return false;
      ++i;
    }
  return true;
}

consteval bool
can_declared_variable_of (info r)
{
  try { declared_variable_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
can_initializer_of (info r)
{
  try { initializer_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

// Whether FN's body is the declaration of NAMES, all initialized, and N
// statements more.
consteval bool
body_declares (info fn, std::initializer_list<std::string_view> names,
	       std::size_t n = 1)
{
  auto stmts = statements_of (body_of (fn));
  return stmts.size () == n + 1 && declares (stmts[0], names);
}

// The control: separate declarations are separate statements.
static_assert (statements_of (body_of (^^separate)).size () == 3);
static_assert (declares (statements_of (body_of (^^separate))[0], {"a"}));
static_assert (can_declared_variable_of (statements_of (body_of (^^separate))[0]));

static_assert (body_declares (^^two, {"a", "b"}));
static_assert (body_declares (^^three, {"a", "b", "c"}));
static_assert (statements_of (body_of (^^mixed)).size () == 3);
static_assert (declares (statements_of (body_of (^^mixed))[0],
			 {"a", "p", "c"}, {"c"}));
static_assert (body_declares (^^ctor, {"a", "b"}));
static_assert (body_declares (^^dtor, {"a", "b"}));
static_assert (body_declares (^^aggr, {"a", "b"}));
static_assert (body_declares (^^nrv_first, {"a", "b"}));
static_assert (body_declares (^^nrv_second, {"a", "b"}));
static_assert (body_declares (^^cx, {"a", "b"}));
static_assert (body_declares (^^tmpl<double>, {"a", "b"}));
static_assert (statements_of (body_of (^^lambda<double>)).size () == 3);
static_assert (declares (statements_of (body_of (^^lambda<double>))[1],
			 {"a", "b"}));

// A declaration of more than one variable has no one variable.
static_assert (!can_declared_variable_of (statements_of (body_of (^^two))[0]));
static_assert (!can_initializer_of (statements_of (body_of (^^two))[0]));

// The inner block of in_block.
static_assert (statements_of (body_of (^^in_block)).size () == 3);
static_assert (statements_of (statements_of (body_of (^^in_block))[1]).size ()
	       == 2);
static_assert (declares (statements_of (statements_of
					(body_of (^^in_block))[1])[0],
			 {"a", "b"}));
