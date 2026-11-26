// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-unused-label" }
// A declaration that extends the lifetime of a temporary is one statement,
// as on clang: the variable that holds the temporary, which GCC declares
// ahead of it, is part of its initializer (cpp_reflection_ad#293).  So is
// the array of a std::initializer_list.

#include <meta>
#include <string>
#include <initializer_list>

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

consteval info
st (info fn, std::size_t i)
{
  return statements_of (body_of (fn))[i];
}

struct T { ~T () {} int v = 1; };
struct U { int v = 1; };
struct A { const T &t; };
struct P { int a, b; };
int sink (int x) { return x; }

int with_dtor (int) { const T &r = T{}; return r.v; }
int trivial (int) { const U &r = U{}; return r.v; }
int scalar (int) { const int &i = 5; return i; }
int rvalue (int) { T &&r = T{}; return r.v; }
int forwarding (int) { auto &&r = T{}; return r.v; }
int static_local (int) { static const T &s = T{}; return s.v; }
int init_list (int) { std::initializer_list<int> l = {1, 2, 3}; return l.size (); }
int aggregate (int) { A a{T{}}; return a.t.v; }
int conditional (int x) { const T &r = x ? T{} : T{}; return r.v; }
int two (int) { const T &a = T{}, &b = T{}; return a.v + b.v; }
int labeled (int) { l: const T &r = T{}; return r.v; }
int nested (int x) { { const T &r = T{}; sink (r.v); } return x; }
int if_init (int) { if (const T &r = T{}; r.v) return 1; return 0; }
consteval int immediate () { const U &r = U{}; return r.v; }
template <typename X> X in_template (X x) { const T &r = T{}; return x + r.v; }
template int in_template (int);

// Unchanged: a structured binding's variable has no name either.
int binding (int) { auto [a, b] = P{1, 2}; return a + b; }

static_assert (body_shape (^^with_dtor) == "C(D R)");
static_assert (body_shape (^^trivial) == "C(D R)");
static_assert (body_shape (^^scalar) == "C(D R)");
static_assert (body_shape (^^rvalue) == "C(D R)");
static_assert (body_shape (^^forwarding) == "C(D R)");
static_assert (body_shape (^^static_local) == "C(D R)");
static_assert (body_shape (^^init_list) == "C(D R)");
static_assert (body_shape (^^aggregate) == "C(D R)");
static_assert (body_shape (^^conditional) == "C(D R)");
static_assert (body_shape (^^two) == "C(D R)");
static_assert (initializers_of (st (^^two, 0)).size () == 2);
static_assert (body_shape (^^labeled) == "C(L(D) R)");
static_assert (body_shape (^^nested) == "C(C(D E) R)");
static_assert (body_shape (^^if_init) == "C(If(D E R) R)");
static_assert (body_shape (^^immediate) == "C(D R)");
static_assert (body_shape (^^in_template<int>) == "C(D R)");
static_assert (body_shape (^^binding) == "C(D R)");

// The declaration's initializer is an expression.
static_assert (initializers_of (st (^^with_dtor, 0)).size () == 1);
static_assert (is_expression (initializers_of (st (^^with_dtor, 0))[0]));
static_assert (is_expression (initializer_of (st (^^conditional, 0))));
