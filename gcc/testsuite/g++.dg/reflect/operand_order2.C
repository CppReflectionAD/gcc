// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// More operators that are reflected as written, in templates and constexpr
// functions too.  An operator whose operands are all constant is still
// folded.

#include <meta>

using namespace std::meta;

void f (int x, int y, bool a, bool b)
{
  bool q0 = !(x < y);
  bool q1 = !!a;
  int q2 = x + 0;
  bool q3 = true && a;
  int q4 = x * 1;
  bool q5 = a == a;
  int q6 = (1 + 2) * x;
}

template <typename T>
T g (T d, int p)
{
  T q = d + p;
  return q;
}
template double g (double, int);

constexpr double cf (double d, int p)
{
  double q = d + p;
  bool r = !(d < 0 || p < 0);
  return r ? q : -q;
}
static_assert (cf (1.0, 2) == 3.0);
static_assert (cf (-1.0, 2) == -1.0);

consteval info strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}
consteval info init (info fn, int i)
{
  return strip (initializer_of (statements_of (body_of (fn))[i]));
}
consteval info op (info e, int i) { return strip (operands_of (e)[i]); }
consteval bool names (info e, std::string_view n)
{
  return is_id_expression (e) && identifier_of (declaration_of (e)) == n;
}
consteval operators oper (info e) { return expression_operator_of (e); }

// !(x < y) isn't x >= y.
static_assert (oper (init (^^f, 0)) == operators::op_exclamation);
static_assert (oper (op (init (^^f, 0), 0)) == operators::op_less);
// !!a isn't a.
static_assert (oper (init (^^f, 1)) == operators::op_exclamation);
static_assert (oper (op (init (^^f, 1), 0)) == operators::op_exclamation);
// x + 0 isn't x.
static_assert (oper (init (^^f, 2)) == operators::op_plus);
static_assert (names (op (init (^^f, 2), 0), "x"));
static_assert (is_literal (op (init (^^f, 2), 1)));
// true && a isn't a.
static_assert (oper (init (^^f, 3)) == operators::op_ampersand_ampersand);
static_assert (is_literal (op (init (^^f, 3), 0)));
// x * 1 isn't x.
static_assert (oper (init (^^f, 4)) == operators::op_star);
// a == a isn't true.
static_assert (oper (init (^^f, 5)) == operators::op_equals_equals);
// 1 + 2 is folded: (1 + 2) * x is 3 * x.
static_assert (oper (init (^^f, 6)) == operators::op_star);
static_assert (is_literal (op (init (^^f, 6), 0)));
static_assert (names (op (init (^^f, 6), 1), "x"));

// A template instance.
static_assert (names (op (init (^^g<double>, 0), 0), "d"));
static_assert (names (op (init (^^g<double>, 0), 1), "p"));

// A constexpr function.
static_assert (names (op (init (^^cf, 0), 0), "d"));
static_assert (oper (init (^^cf, 1)) == operators::op_exclamation);
static_assert (oper (op (init (^^cf, 1), 0)) == operators::op_pipe_pipe);
