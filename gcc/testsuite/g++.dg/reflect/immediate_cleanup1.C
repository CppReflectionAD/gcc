// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-unused-label" }
// The body of an immediate function is reflected as that of any other
// function, as on clang, though GCC never genericizes it: a statement after
// a local with a destructor keeps its kind (cpp_reflection_ad#299).

#include <meta>
#include <string>

using namespace std::meta;

// The kinds of the statements in S, nested: C a block, L a label, If, S
// another statement with parts, D a declaration, R a return, E an
// expression or an expression statement.
consteval std::string
shape (info s)
{
  if (is_expression (s) || is_expression_statement (s))
    return "E";
  if (is_declaration_statement (s))
    return "D";
  if (is_return_statement (s))
    return "R";
  std::string r = (is_compound_statement (s) ? "C"
		   : is_label_statement (s) ? "L"
		   : is_if_statement (s) ? "If" : "S");
  auto parts = statements_of (s);
  if (!parts.empty ())
    {
      r += "(";
      for (std::size_t i = 0; i < parts.size (); ++i)
	r += (i ? " " : "") + shape (parts[i]);
      r += ")";
    }
  return r;
}

consteval std::string
body_shape (info fn)
{
  return shape (body_of (fn));
}

struct T { constexpr ~T () {} int v = 1; };

// Each body twice: in an immediate function, and in one that isn't.
#define BOTH(name, body) \
  consteval int ce_##name (int x) { body } \
  constexpr int cx_##name (int x) { body }

BOTH (dtor_return, T t; return t.v + x;)
BOTH (dtor_two, T a; T b; return a.v + b.v + x;)
BOTH (dtor_nested, { T t; x += t.v; } return x;)
BOTH (dtor_if, if (x) { T t; return t.v; } return 0;)
BOTH (dtor_if_init, if (T t; x) return t.v; return 0;)
BOTH (dtor_switch_init, switch (T t; x) { case 1: return t.v; } return 0;)
BOTH (dtor_while, while (x) { T t; x -= t.v; } return x;)
BOTH (dtor_label, l: T t; return t.v + x;)
BOTH (named_return, T t; t.v = x; return t.v;)
BOTH (plain_if, if (x) return 1; return 0;)

#define SAME(name, s) \
  static_assert (body_shape (^^ce_##name) == s); \
  static_assert (body_shape (^^cx_##name) == s)

SAME (dtor_return, "C(D R)");
SAME (dtor_two, "C(D D R)");
SAME (dtor_nested, "C(C(D E) R)");
SAME (dtor_if, "C(If(E C(D R)) R)");
SAME (dtor_if_init, "C(If(D E R) R)");
SAME (dtor_switch_init, "C(S(D E C(S(E R))) R)");
SAME (dtor_while, "C(S(E C(D E)) R)");
SAME (dtor_label, "C(L(D) R)");
SAME (named_return, "C(D E R)");
SAME (plain_if, "C(If(E R) R)");

// The local's declaration has its initializer.
static_assert (initializers_of (statements_of (body_of (^^ce_dtor_return))[0])
	       .size () == 1);
static_assert (is_return_statement (statements_of (body_of (^^ce_dtor_return))[1]));

static_assert (ce_dtor_return (1) == 2);
