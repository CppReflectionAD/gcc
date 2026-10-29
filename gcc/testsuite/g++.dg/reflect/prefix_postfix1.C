// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::is_prefix and std::meta::is_postfix (P4395R0).

#include <meta>

using namespace std::meta;

constexpr int
builtin_inc_dec (int x)
{
  ++x;
  --x;
  x++;
  x--;
  +x;
  -x;
  x += 1;
  return x + 1;
}

struct Counter
{
  int v;
  constexpr Counter &operator++ () { ++v; return *this; }
  constexpr Counter &operator-- () { --v; return *this; }
  constexpr Counter operator++ (int) { Counter old = *this; ++v; return old; }
  constexpr Counter operator-- (int) { Counter old = *this; --v; return old; }
};

constexpr int
overloaded_member_inc_dec (Counter c)
{
  ++c;
  --c;
  c++;
  c--;
  c.operator++ ();
  c.operator++ (0);
  return c.v;
}

struct Tag { int v; };
constexpr Tag &operator++ (Tag &t) { ++t.v; return t; }
constexpr Tag &operator-- (Tag &t) { --t.v; return t; }
constexpr Tag operator++ (Tag &t, int) { Tag old = t; ++t.v; return old; }
constexpr Tag operator-- (Tag &t, int) { Tag old = t; --t.v; return old; }

constexpr int
overloaded_free_inc_dec (Tag t)
{
  ++t;
  --t;
  t++;
  t--;
  return t.v;
}

// Built-in ++/--
constexpr info b0 = expression_of (statements_of (body_of (^^builtin_inc_dec))[0]);
constexpr info b1 = expression_of (statements_of (body_of (^^builtin_inc_dec))[1]);
constexpr info b2 = expression_of (statements_of (body_of (^^builtin_inc_dec))[2]);
constexpr info b3 = expression_of (statements_of (body_of (^^builtin_inc_dec))[3]);
constexpr info b4 = expression_of (statements_of (body_of (^^builtin_inc_dec))[4]);
constexpr info b5 = expression_of (statements_of (body_of (^^builtin_inc_dec))[5]);
constexpr info b6 = expression_of (statements_of (body_of (^^builtin_inc_dec))[6]);
constexpr info b7 = return_operand_of (statements_of (body_of (^^builtin_inc_dec))[7]);

static_assert (is_prefix (b0) && !is_postfix (b0));
static_assert (operator_of (b0) == operators::op_plus_plus);
static_assert (is_prefix (b1) && !is_postfix (b1));
static_assert (operator_of (b1) == operators::op_minus_minus);
static_assert (!is_prefix (b2) && is_postfix (b2));
static_assert (operator_of (b2) == operators::op_plus_plus);
static_assert (!is_prefix (b3) && is_postfix (b3));
static_assert (operator_of (b3) == operators::op_minus_minus);

// Other unary/binary operators are neither prefix nor postfix ++/--
static_assert (!is_prefix (b4) && !is_postfix (b4));
static_assert (!is_prefix (b5) && !is_postfix (b5));
static_assert (!is_prefix (b6) && !is_postfix (b6));
static_assert (!is_prefix (b7) && !is_postfix (b7));

// Overloaded member ++/--
constexpr info m0 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[0]);
constexpr info m1 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[1]);
constexpr info m2 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[2]);
constexpr info m3 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[3]);
constexpr info m4 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[4]);
constexpr info m5 = expression_of (statements_of (body_of (^^overloaded_member_inc_dec))[5]);

static_assert (is_prefix (m0) && !is_postfix (m0));
static_assert (operator_of (m0) == operators::op_plus_plus);
static_assert (is_prefix (m1) && !is_postfix (m1));
static_assert (operator_of (m1) == operators::op_minus_minus);
static_assert (!is_prefix (m2) && is_postfix (m2));
static_assert (operator_of (m2) == operators::op_plus_plus);
static_assert (!is_prefix (m3) && is_postfix (m3));
static_assert (operator_of (m3) == operators::op_minus_minus);

// Explicit member call syntax `c.operator++()` is not an operator expression
static_assert (!is_prefix (m4) && !is_postfix (m4));
static_assert (!is_prefix (m5) && !is_postfix (m5));

// Overloaded non-member ++/--
constexpr info f0 = expression_of (statements_of (body_of (^^overloaded_free_inc_dec))[0]);
constexpr info f1 = expression_of (statements_of (body_of (^^overloaded_free_inc_dec))[1]);
constexpr info f2 = expression_of (statements_of (body_of (^^overloaded_free_inc_dec))[2]);
constexpr info f3 = expression_of (statements_of (body_of (^^overloaded_free_inc_dec))[3]);

static_assert (is_prefix (f0) && !is_postfix (f0));
static_assert (operator_of (f0) == operators::op_plus_plus);
static_assert (is_prefix (f1) && !is_postfix (f1));
static_assert (operator_of (f1) == operators::op_minus_minus);
static_assert (!is_prefix (f2) && is_postfix (f2));
static_assert (operator_of (f2) == operators::op_plus_plus);
static_assert (!is_prefix (f3) && is_postfix (f3));
static_assert (operator_of (f3) == operators::op_minus_minus);

// Non-expression reflections return false (no exception).
static_assert (!is_prefix (info{}) && !is_postfix (info{}));
static_assert (!is_prefix (^^int) && !is_postfix (^^int));
static_assert (!is_prefix (^^builtin_inc_dec) && !is_postfix (^^builtin_inc_dec));
static_assert (!is_prefix (body_of (^^builtin_inc_dec))
	       && !is_postfix (body_of (^^builtin_inc_dec)));
static_assert (!is_prefix (statements_of (body_of (^^builtin_inc_dec))[0])
	       && !is_postfix (statements_of (body_of (^^builtin_inc_dec))[0]));
