// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A null statement is an expression statement with no expression
// ([stmt.expr]), so statements_of gives it and is_expression_statement holds.

#include <meta>

using namespace std::meta;

double f_null (double x) { ; return x; }
double f_two (double x) { ;; return x; }
double f_end (double x) { return x; ; }
template <class T> T t_null (T x) { ; return x; }
double f_void (double x) { (void) 0; return x; }

consteval info
stmt (info fn, unsigned i)
{
  return statements_of (body_of (fn))[i];
}

consteval bool
null_p (info s)
{
  return (is_statement (s)
	  && is_expression_statement (s)
	  && !is_declaration_statement (s)
	  && !is_return_statement (s)
	  && !is_compound_statement (s));
}

consteval bool
throws_expression_of (info s)
{
  try { expression_of (s); }
  catch (const exception &) { return true; }
  return false;
}

static_assert (statements_of (body_of (^^f_null)).size () == 2);
static_assert (null_p (stmt (^^f_null, 0)));
static_assert (is_return_statement (stmt (^^f_null, 1)));
static_assert (throws_expression_of (stmt (^^f_null, 0)));

static_assert (statements_of (body_of (^^f_two)).size () == 3);
static_assert (null_p (stmt (^^f_two, 0)));
static_assert (null_p (stmt (^^f_two, 1)));

static_assert (statements_of (body_of (^^f_end)).size () == 2);
static_assert (is_return_statement (stmt (^^f_end, 0)));
static_assert (null_p (stmt (^^f_end, 1)));

constexpr info tn = ^^t_null<double>;
static_assert (statements_of (body_of (tn)).size () == 2);
static_assert (null_p (stmt (tn, 0)));

// An expression statement that has an expression still gives it.
static_assert (statements_of (body_of (^^f_void)).size () == 2);
static_assert (is_expression_statement (stmt (^^f_void, 0)));
static_assert (!throws_expression_of (stmt (^^f_void, 0)));
