// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-unused-label" }
// A constant-initialized static local with a non-trivial destructor is one
// declaration statement, although expand_static_init registers the
// destructor in an `if' on its guard variable after the declaration
// (cpp_reflection_ad#298).

#include <meta>

using namespace std::meta;

struct D { constexpr D () {} constexpr D (int x) : v (x) {} ~D () {} int v = 1; };

int d_default (int x) { static D b; return b.v + x; }
int d_paren (int x) { static D b (2); return b.v + x; }
int d_brace (int x) { static D b{2}; return b.v + x; }
int d_copy (int x) { static D b = 2; return b.v + x; }
int d_constinit (int x) { static constinit D b (2); return b.v + x; }
int d_tl (int x) { thread_local D b; return b.v + x; }
int d_arr (int x) { static D b[2]; return b[0].v + x; }
template <typename U> int tmpl (int x) { static U b; return b.v + x; }
template int tmpl<D> (int);
// Controls: a dynamic initializer, which #230 folded into the declaration.
int d_dynamic (int x) { static D b (x); return b.v; }

int
two (int x)
{
  static D b;
  static D c (x);
  return b.v + c.v;
}

int
in_block (int x)
{
  {
    static D b;
    x += b.v;
  }
  return x;
}

int
labeled (int x)
{
l:
  static D b;
  return b.v + x;
}

// Whether STMT is the declaration of b.
consteval bool
declares_b (info stmt)
{
  return (is_declaration_statement (stmt) && !is_expression_statement (stmt)
	  && identifier_of (declared_variable_of (stmt)) == "b");
}

// Whether FN's body is b's declaration and a return.
consteval bool
body_is_one_declaration (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2 && declares_b (stmts[0])
	  && is_return_statement (stmts[1]));
}

static_assert (body_is_one_declaration (^^d_default));
static_assert (body_is_one_declaration (^^d_paren));
static_assert (body_is_one_declaration (^^d_brace));
static_assert (body_is_one_declaration (^^d_copy));
static_assert (body_is_one_declaration (^^d_constinit));
static_assert (body_is_one_declaration (^^d_tl));
static_assert (body_is_one_declaration (^^d_arr));
static_assert (body_is_one_declaration (^^tmpl<D>));
static_assert (body_is_one_declaration (^^d_dynamic));

// A constant initializer is still the declaration's initializer.
static_assert (initializers_of (statements_of (body_of (^^d_paren))[0]).size ()
	       == 1);

static_assert (statements_of (body_of (^^two)).size () == 3);
static_assert (declares_b (statements_of (body_of (^^two))[0]));
static_assert (is_declaration_statement (statements_of (body_of (^^two))[1]));

static_assert (statements_of (body_of (^^in_block)).size () == 2);
static_assert (statements_of (statements_of (body_of (^^in_block))[0]).size ()
	       == 2);
static_assert (declares_b
	       (statements_of (statements_of (body_of (^^in_block))[0])[0]));

static_assert (statements_of (body_of (^^labeled)).size () == 2);
static_assert (declares_b (statements_of (statements_of (body_of (^^labeled))[0])[0]));
