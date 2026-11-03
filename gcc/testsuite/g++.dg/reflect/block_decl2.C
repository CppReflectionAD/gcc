// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A typedef, an alias-declaration, and a declaration of a local class or
// enumeration with no declarators are each a declaration statement that
// isn't a simple declaration (cpp_reflection_ad#235).

#include <meta>

using namespace std::meta;

double f_alias (double x) { using T = double; return T (x); }
double f_typedef (double x) { typedef double T; return T (x); }
double f_class (double x) { struct L { double v; }; return L{x}.v; }
double f_enum (double x) { enum E { a, b }; return x + int (b); }
double f_scoped_enum (double x) { enum class E : int { a, b }; return x + int (E::b); }
double f_unnamed_enum (double x) { enum { a, b }; return x + int (b); }
double f_typedef_class (double x) { typedef struct { double v; } S; return S{x}.v; }
double f_forward (double x) { struct F; return x; }
double f_member_typedef (double x) { struct L { typedef double T; T v; }; return L{x}.v; }

template <typename T> T t_alias (T x) { using U = T; return U (x); }
template <typename T> T t_typedef (T x) { typedef T U; return U (x); }
template <typename T> T t_class (T x) { struct L { T v; }; return L{x}.v; }
template <typename T> T t_enum (T x) { enum E { a, b }; return x + int (b); }
template <typename T> T t_forward (T x) { struct F; return x; }
template <typename T> struct C
{
  static T f (T x) { struct L { T v; }; return L{x}.v; }
};
template <typename T> T t_member (T x)
{
  struct O { static T f (T y) { struct I { T v; }; return I{y}.v; } };
  return O::f (x);
}
template double t_alias<double> (double);
template double t_typedef<double> (double);
template double t_class<double> (double);
template double t_enum<double> (double);
template double t_forward<double> (double);
template struct C<double>;
template double t_member<double> (double);

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

static_assert (declaration_then_return (^^f_alias));
static_assert (declaration_then_return (^^f_typedef));
static_assert (declaration_then_return (^^f_class));
static_assert (declaration_then_return (^^f_enum));
static_assert (declaration_then_return (^^f_scoped_enum));
static_assert (declaration_then_return (^^f_unnamed_enum));
static_assert (declaration_then_return (^^f_typedef_class));
static_assert (declaration_then_return (^^f_forward));
static_assert (declaration_then_return (^^f_member_typedef));
static_assert (declaration_then_return (^^t_alias<double>));
static_assert (declaration_then_return (^^t_typedef<double>));
static_assert (declaration_then_return (^^t_class<double>));
static_assert (declaration_then_return (^^t_enum<double>));
static_assert (declaration_then_return (^^t_forward<double>));
static_assert (declaration_then_return (^^C<double>::f));
static_assert (declaration_then_return (^^t_member<double>));

// A class defined in a declaration with a declarator is still declared by
// the one simple declaration, in a template too, as is a lambda's closure
// type.
double f_class_var (double x) { struct L { double v; } l{x}; return l.v; }
template <typename T> T t_class_var (T x) { struct L { T v; } l{x}; return l.v; }
template double t_class_var<double> (double);
double f_lambda (double x) { auto g = [] (double y) { return y; }; return g (x); }

consteval bool
simple_then_return (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2
	  && is_simple_declaration (stmts[0])
	  && declarators_of (stmts[0]).size () == 1
	  && is_return_statement (stmts[1]));
}

static_assert (simple_then_return (^^f_class_var));
static_assert (simple_then_return (^^t_class_var<double>));
static_assert (simple_then_return (^^f_lambda));

// The declarations in a generic lambda.
template <typename T> T t_generic_lambda (T x)
{
  auto g = [] (auto y) {
    struct L { decltype (y) v; };
    using U = decltype (y);
    return U (L{y}.v);
  };
  return g (x);
}
template double t_generic_lambda<double> (double);

// Each of these in a function that is constant evaluated.
constexpr double
c_all (double x)
{
  using A = double;
  typedef double B;
  struct L { double v; };
  enum E { a, b };
  struct F;
  return A (L{x}.v) + B (int (b));
}
static_assert (c_all (1.0) == 2.0);
static_assert (statements_of (body_of (^^c_all)).size () == 6);

int
main ()
{
  double r = (f_alias (1) + f_typedef (1) + f_class (1) + f_enum (1)
	      + f_scoped_enum (1) + f_unnamed_enum (1) + f_typedef_class (1)
	      + f_forward (1) + f_member_typedef (1) + t_alias (1.0)
	      + t_typedef (1.0) + t_class (1.0) + t_enum (1.0)
	      + t_forward (1.0) + C<double>::f (1) + t_member (1.0)
	      + f_class_var (1) + t_class_var (1.0) + f_lambda (1)
	      + t_generic_lambda (1.0) + c_all (1));
  if (r != 26)
    __builtin_abort ();
}
