// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A static_assert-declaration, a consteval block, a namespace alias, a
// using-declaration, and a using-directive are each a declaration statement
// that isn't a simple declaration (cpp_reflection_ad#235).

#include <meta>

using namespace std::meta;

namespace N
{
  double g (double x) { return x; }
  double g (int x) { return x; }
  double v = 1;
  enum class E { a, b };
}

double f_assert (double x) { static_assert (sizeof (double) == 8); return x; }
double f_consteval_block (double x) { consteval { } return x; }
double f_namespace_alias (double x) { namespace M = N; return M::g (x); }
double f_using (double x) { using N::g; return g (x); }
double f_using_variable (double x) { using N::v; return v * x; }
double f_using_list (double x) { using N::g, N::v; return v * g (x); }
double f_using_directive (double x) { using namespace N; return g (x); }
double f_using_enum (double x) { using enum N::E; return x + int (b); }

template <typename T> T t_assert (T x) { static_assert (sizeof (T) == 8); return x; }
template <typename T> T t_assert_nondep (T x) { static_assert (true); return x; }
template <typename T> T t_consteval_block (T x) { consteval { } return x; }
template <typename T> T t_namespace_alias (T x) { namespace M = N; return M::g (x); }
template <typename T> T t_using (T x) { using N::g; return g (x); }
template <typename T> T t_using_list (T x) { using N::g, N::v; return v * g (x); }
template <typename T> T t_using_directive (T x) { using namespace N; return g (x); }
template <typename T> T t_using_enum (T x) { using enum N::E; return x + int (b); }
template <typename E> double t_using_dependent (double x) { using E::b; return x + int (b); }
template double t_assert<double> (double);
template double t_assert_nondep<double> (double);
template double t_consteval_block<double> (double);
template double t_namespace_alias<double> (double);
template double t_using<double> (double);
template double t_using_list<double> (double);
template double t_using_directive<double> (double);
template double t_using_enum<double> (double);
template double t_using_dependent<N::E> (double);

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

static_assert (declaration_then_return (^^f_assert));
static_assert (declaration_then_return (^^f_consteval_block));
static_assert (declaration_then_return (^^f_namespace_alias));
static_assert (declaration_then_return (^^f_using));
static_assert (declaration_then_return (^^f_using_variable));
static_assert (declaration_then_return (^^f_using_list));
static_assert (declaration_then_return (^^f_using_directive));
static_assert (declaration_then_return (^^f_using_enum));
static_assert (declaration_then_return (^^t_assert<double>));
static_assert (declaration_then_return (^^t_assert_nondep<double>));
static_assert (declaration_then_return (^^t_consteval_block<double>));
static_assert (declaration_then_return (^^t_namespace_alias<double>));
static_assert (declaration_then_return (^^t_using<double>));
static_assert (declaration_then_return (^^t_using_list<double>));
static_assert (declaration_then_return (^^t_using_directive<double>));
static_assert (declaration_then_return (^^t_using_enum<double>));
static_assert (declaration_then_return (^^t_using_dependent<N::E>));

// An expression statement that does nothing is still one.
double f_void (double x) { (void) 0; return x; }

consteval bool
expression_then_return (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2
	  && is_expression_statement (stmts[0])
	  && !is_declaration_statement (stmts[0])
	  && is_return_statement (stmts[1]));
}

static_assert (expression_then_return (^^f_void));

// Each of these in a function that is constant evaluated.
constexpr double
c_all (double x)
{
  static_assert (true);
  consteval { }
  namespace M = N;
  using N::E;
  using namespace N;
  return x + int (E::b);
}
static_assert (c_all (1.0) == 2.0);
static_assert (statements_of (body_of (^^c_all)).size () == 6);

int
main ()
{
  double r = (f_assert (1) + f_consteval_block (1) + f_namespace_alias (1)
	      + f_using (1) + f_using_variable (1) + f_using_list (1)
	      + f_using_directive (1)
	      + f_using_enum (1) + t_assert (1.0) + t_assert_nondep (1.0)
	      + t_consteval_block (1.0) + t_namespace_alias (1.0)
	      + t_using (1.0) + t_using_list (1.0) + t_using_directive (1.0)
	      + t_using_enum (1.0) + t_using_dependent<N::E> (1) + f_void (1)
	      + c_all (1));
  if (r != 23)
    __builtin_abort ();
}
