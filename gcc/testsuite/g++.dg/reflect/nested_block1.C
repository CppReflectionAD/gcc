// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A block is a compound statement ([stmt.block]) whether or not it declares
// anything, so statements_of gives it in the block it is in, and its own
// statements only inside it.

#include <meta>

using namespace std::meta;

double f_decl (double x) { { int a = 0; } return x; }
double f_empty (double x) { { } return x; }
double f_expr (double x) { { x + 1; } return x; }
double f_two (double x) { { x + 1; x + 2; } return x; }
double f_null (double x) { { ; } return x; }
double f_nested (double x) { { { } } return x; }
double f_nested_decl (double x) { { { int a = 0; } } return x; }
double f_only (double x) { { return x; } }
void v_only_decl () { { int a = 0; } }
void v_only_empty () { { } }
template <class T> T t_empty (T x) { { } return x; }
template <class T> T t_expr (T x) { { x + 1; } return x; }
template <class T> T t_nested (T x) { { { x + 1; } } return x; }

consteval info
stmt (info s, unsigned i)
{
  return statements_of (s)[i];
}

consteval unsigned
count (info s)
{
  return statements_of (s).size ();
}

consteval bool
block_p (info s, unsigned n)
{
  return (is_statement (s)
	  && is_compound_statement (s)
	  && !is_expression_statement (s)
	  && !is_declaration_statement (s)
	  && !is_return_statement (s)
	  && count (s) == n);
}

// Statement I of the first statement of FN's body.
consteval info
inner (info fn, unsigned i)
{
  return stmt (stmt (body_of (fn), 0), i);
}

// A block followed by a return, with N statements in the block.
consteval bool
block_then_return (info fn, unsigned n)
{
  info b = body_of (fn);
  return (count (b) == 2
	  && block_p (stmt (b, 0), n)
	  && is_return_statement (stmt (b, 1)));
}

static_assert (block_then_return (^^f_decl, 1));
static_assert (is_declaration_statement (inner (^^f_decl, 0)));

static_assert (block_then_return (^^f_empty, 0));

static_assert (block_then_return (^^f_expr, 1));
static_assert (is_expression_statement (inner (^^f_expr, 0)));

static_assert (block_then_return (^^f_two, 2));
static_assert (is_expression_statement (inner (^^f_two, 1)));

static_assert (block_then_return (^^f_null, 1));
static_assert (is_expression_statement (inner (^^f_null, 0)));

static_assert (block_then_return (^^f_nested, 1));
static_assert (block_p (inner (^^f_nested, 0), 0));

static_assert (block_then_return (^^f_nested_decl, 1));
static_assert (block_p (inner (^^f_nested_decl, 0), 1));

static_assert (count (body_of (^^f_only)) == 1);
static_assert (block_p (stmt (body_of (^^f_only), 0), 1));
static_assert (is_return_statement (inner (^^f_only, 0)));
static_assert (body_of (^^f_only) == body_of (^^f_only));
static_assert (body_of (^^f_only) != stmt (body_of (^^f_only), 0));

static_assert (count (body_of (^^v_only_decl)) == 1);
static_assert (block_p (stmt (body_of (^^v_only_decl), 0), 1));
static_assert (count (body_of (^^v_only_empty)) == 1);
static_assert (block_p (stmt (body_of (^^v_only_empty), 0), 0));

static_assert (block_then_return (^^t_empty<double>, 0));
static_assert (block_then_return (^^t_expr<double>, 1));
static_assert (block_then_return (^^t_nested<double>, 1));
static_assert (block_p (inner (^^t_nested<double>, 0), 1));
