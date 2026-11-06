// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A static local with a dynamic initializer is one declaration statement,
// with its initializer, although expand_static_init initializes it in an
// `if' on its guard variable after the declaration (cpp_reflection_ad#230).

#include <meta>

using namespace std::meta;

struct C { constexpr C (double x) : v (x) {} double v; };
struct D { D (double x) : v (x) {} ~D (); double v; };
struct T { double v; };

double g (double);

double s_scalar (double x) { static double b = x; return b; }
double s_call (double x) { static double b = g (x); return b; }
double s_copy (double x) { static C b = x; return b.v; }
double s_paren (double x) { static C b (x); return b.v; }
double s_brace (double x) { static C b{x}; return b.v; }
double s_dtor (double x) { static D b (x); return b.v; }
double s_aggr (double x) { static T b = {x}; return b.v; }
double s_arr (double x) { static double b[2] = {x, x}; return b[0]; }
double s_tl (double x) { thread_local double b = x; return b; }
template <typename U> U tmpl (U x) { static U b = x; return b; }
template double tmpl<double> (double);
// Controls: a constant initialization has no guard.
double s_const (double) { static C b (1.0); return b.v; }
double s_const_scalar (double) { static double b = 1.0; return b; }

double
s_assign (double x)
{
  static double b = x;
  b = 2 * x;
  return b;
}

double
two (double x)
{
  static double b = x;
  static C c (x);
  return b + c.v;
}

double
in_block (double x)
{
  double s = 0;
  {
    static C b (x);
    s = b.v;
  }
  return s;
}

// Whether STMT is the declaration of b, with an initializer.
consteval bool
initialized_declaration (info stmt)
{
  if (!is_declaration_statement (stmt) || is_expression_statement (stmt)
      || identifier_of (declared_variable_of (stmt)) != "b")
    return false;
  auto inits = initializers_of (stmt);
  return (inits.size () == 1 && inits[0] != info{}
	  && initializer_of (declared_variable_of (stmt)) == inits[0]);
}

// Whether FN's body is b's declaration, with an initializer, and a return.
consteval bool
body_is_one_initialized_declaration (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2 && initialized_declaration (stmts[0])
	  && is_return_statement (stmts[1]));
}

// Whether the initializer of FN's first statement constructs b from N
// arguments, rather than calling the constructor.
consteval bool
constructed_from (info fn, std::size_t n)
{
  info init = initializers_of (statements_of (body_of (fn))[0])[0];
  return !is_function_call (init) && operands_of (init).size () == n;
}

static_assert (body_is_one_initialized_declaration (^^s_const));
static_assert (body_is_one_initialized_declaration (^^s_const_scalar));
static_assert (body_is_one_initialized_declaration (^^s_scalar));
static_assert (body_is_one_initialized_declaration (^^s_call));
static_assert (body_is_one_initialized_declaration (^^s_copy));
static_assert (body_is_one_initialized_declaration (^^s_paren));
static_assert (body_is_one_initialized_declaration (^^s_brace));
static_assert (body_is_one_initialized_declaration (^^s_dtor));
static_assert (body_is_one_initialized_declaration (^^s_aggr));
static_assert (body_is_one_initialized_declaration (^^s_arr));
static_assert (body_is_one_initialized_declaration (^^s_tl));
static_assert (body_is_one_initialized_declaration (^^tmpl<double>));

static_assert (constructed_from (^^s_copy, 1));
static_assert (constructed_from (^^s_paren, 1));
static_assert (constructed_from (^^s_brace, 1));
static_assert (constructed_from (^^s_dtor, 1));
static_assert (is_function_call (initializers_of
				 (statements_of (body_of (^^s_call))[0])[0]));

// The assignment after the declaration is a statement of its own.
static_assert (statements_of (body_of (^^s_assign)).size () == 3);
static_assert (initialized_declaration (statements_of (body_of (^^s_assign))[0]));
static_assert (is_expression_statement
	       (statements_of (body_of (^^s_assign))[1]));

// Two static locals, each with its own guard.
static_assert (statements_of (body_of (^^two)).size () == 3);
static_assert (initialized_declaration (statements_of (body_of (^^two))[0]));
static_assert (is_declaration_statement (statements_of (body_of (^^two))[1]));
static_assert (initializers_of (statements_of (body_of (^^two))[1])[0]
	       != info{});

// The inner block of in_block.
static_assert (statements_of (body_of (^^in_block)).size () == 3);
static_assert (statements_of (statements_of (body_of (^^in_block))[1]).size ()
	       == 2);
static_assert (initialized_declaration
	       (statements_of (statements_of (body_of (^^in_block))[1])[0]));
