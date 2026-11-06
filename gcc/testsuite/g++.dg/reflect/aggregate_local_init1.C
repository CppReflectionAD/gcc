// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A local aggregate or array with a non-constant initializer is one
// declaration statement, and its variable has an initializer, although
// store_init_value splits the initializer into the initializations of the
// variable's subobjects (cpp_reflection_ad#194).

#include <meta>

using namespace std::meta;

struct T { double v; };
struct P { double v, w; };
struct N { T t; double w; };
struct S { double v; double w = 2.0; };
struct D { double v; ~D (); };
struct Q { D d; double w; };
struct C { C (double); double v; };

double t_const (double) { T b = {1.0}; return b.v; }
double t_brace (double x) { T b = {x}; return b.v; }
double t_list (double x) { T b{x}; return b.v; }
double t_paren (double x) { T b (x); return b.v; }
double t_temp (double x) { T b = T{x}; return b.v; }
double t_auto (double x) { auto b = T{x}; return b.v; }
double t_fold (double x) { T b = {x * 1.0}; return b.v; }
double p_brace (double x) { P b = {x, x}; return b.v; }
double p_mixed (double x) { P b = {1.0, x}; return b.w; }
double n_brace (double x) { N b = {{x}, x}; return b.w; }
double s_nsdmi (double x) { S b = {x}; return b.w; }
double d_brace (double x) { D b = {x}; return b.v; }
double q_brace (double x) { Q b = {D{x}, x}; return b.w; }
double arr_brace (double x) { double b[2] = {x, x}; return b[0]; }
double arr_part (double x) { double b[8] = {x}; return b[0]; }
double c_brace (double x) { C b = {x}; return b.v; }
double scalar (double x) { double b{x}; return b; }
template <typename U> U tmpl (U x) { T b = {x}; return b.v; }
template double tmpl<double> (double);
constexpr double cx (double x) { T b = {x}; return b.v; }

double
in_block (double x)
{
  double s = 0;
  {
    T b = {x};
    s = b.v;
  }
  return s;
}

// Whether BLOCK is b's declaration, with an initializer, and then a
// statement that isn't a declaration.
consteval bool
one_initialized_declaration (info block)
{
  auto stmts = statements_of (block);
  if (stmts.size () != 2 || !is_declaration_statement (stmts[0])
      || is_declaration_statement (stmts[1]))
    return false;
  try
    {
      initializer_of (declared_variable_of (stmts[0]));
    }
  catch (const std::meta::exception &)
    {
      return false;
    }
  return true;
}

consteval bool
body_is_one_initialized_declaration (info fn)
{
  return one_initialized_declaration (body_of (fn));
}

static_assert (body_is_one_initialized_declaration (^^t_const));
static_assert (body_is_one_initialized_declaration (^^t_brace));
static_assert (body_is_one_initialized_declaration (^^t_list));
static_assert (body_is_one_initialized_declaration (^^t_paren));
static_assert (body_is_one_initialized_declaration (^^t_temp));
static_assert (body_is_one_initialized_declaration (^^t_auto));
static_assert (body_is_one_initialized_declaration (^^t_fold));
static_assert (body_is_one_initialized_declaration (^^p_brace));
static_assert (body_is_one_initialized_declaration (^^p_mixed));
static_assert (body_is_one_initialized_declaration (^^n_brace));
static_assert (body_is_one_initialized_declaration (^^s_nsdmi));
static_assert (body_is_one_initialized_declaration (^^d_brace));
static_assert (body_is_one_initialized_declaration (^^q_brace));
static_assert (body_is_one_initialized_declaration (^^arr_brace));
static_assert (body_is_one_initialized_declaration (^^arr_part));
static_assert (body_is_one_initialized_declaration (^^c_brace));
static_assert (body_is_one_initialized_declaration (^^scalar));
static_assert (body_is_one_initialized_declaration (^^tmpl<double>));
static_assert (body_is_one_initialized_declaration (^^cx));

// The inner block of in_block.
static_assert (statements_of (body_of (^^in_block)).size () == 3);
static_assert (one_initialized_declaration
	       (statements_of (body_of (^^in_block))[1]));
