// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -O2 -fsanitize=undefined" }
// As statements_of_nrvo1.C, where the front end ends the function with a
// different check for a missing return.

#include <meta>
#include <string_view>
#include <type_traits>

using namespace std::meta;

void destroyed (double);

struct T { double v; };
struct D { double v; ~D () { destroyed (v); } };

static_assert (std::is_trivially_destructible_v<T>);
static_assert (!std::is_trivially_destructible_v<D>);

T make_t (double x) { return {x}; }
D make_d (double x) { return {x}; }

T t_return_local (double x) { T a = make_t (x); return a; }
D d_return_local (double x) { D a = make_d (x); return a; }
D d_return_second (double x) { D a = make_d (x); D b = make_d (a.v); return b; }

// Statements in the source that look like what the front end adds are kept.
int user_unreachable (int x) { if (x) return 1; __builtin_unreachable (); }
int user_empty (int x) { (void) 0; return x; }

consteval info
stmt (info fn, int i)
{
  return statements_of (body_of (fn))[i];
}

consteval bool
declares (info s, std::string_view name)
{
  return (is_declaration_statement (s)
	  && !is_return_statement (s)
	  && identifier_of (declared_variable_of (s)) == name
	  && is_function_call (initializer_of (declared_variable_of (s))));
}

static_assert (is_declaration_statement
	       (statements_of (body_of (^^t_return_local))[0]));
static_assert (is_declaration_statement
	       (statements_of (body_of (^^d_return_local))[0]));
static_assert (statements_of (body_of (^^d_return_local)).size ()
	       == statements_of (body_of (^^t_return_local)).size ());

static_assert (statements_of (body_of (^^d_return_local)).size () == 2);
static_assert (declares (stmt (^^d_return_local, 0), "a"));
static_assert (is_return_statement (stmt (^^d_return_local, 1)));

static_assert (statements_of (body_of (^^d_return_second)).size () == 3);
static_assert (declares (stmt (^^d_return_second, 0), "a"));
static_assert (declares (stmt (^^d_return_second, 1), "b"));
static_assert (is_return_statement (stmt (^^d_return_second, 2)));

static_assert (statements_of (body_of (^^user_unreachable)).size () == 2);
static_assert (statements_of (body_of (^^user_empty)).size () == 2);
