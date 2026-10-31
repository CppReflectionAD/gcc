// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::callee_of and std::meta::operands_of (P4395R0).

#include <meta>

using namespace std::meta;

constexpr int zero_arg () { return 42; }
constexpr int one_arg (int a) { return a + 1; }
constexpr int three_args (int a, int b, int c) { return a + b + c; }

constexpr const int &max_ref (const int &a, const int &b)
{
  return a < b ? b : a;
}

void destroyed (int);
struct D { int v; ~D () { destroyed (v); } };
D make_d (int a, int b) { return {a + b}; }

struct Counter
{
  int v;
  constexpr Counter &operator++ () { ++v; return *this; }
  constexpr Counter operator++ (int) { Counter old = *this; ++v; return old; }
  constexpr int operator* (int x) const { return v * x; }
  constexpr int add (int x) const { return v + x; }
};

constexpr int
calls_body (int x, int y, int (*fp)(int))
{
  int a = zero_arg ();
  int b = one_arg (x);
  int c = three_args (x, y, 10);
  int m = 1 + max_ref (x, y);
  int p = fp (x);
  return a + b + c + m + p;
}

D
call_d_body (int x, int y)
{
  return make_d (x, y);
}

constexpr int
member_calls_body (Counter c, int x)
{
  ++c;
  c++;
  return c.add (x);
}

constexpr int
member_operator_body (Counter c, int x)
{
  return c * x;
}

consteval bool
can_callee_of (info r)
{
  try { callee_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
can_operands_of (info r)
{
  try { operands_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

// 0: int a = zero_arg ();
constexpr info c0 = initializers_of (statements_of (body_of (^^calls_body))[0])[0];
static_assert (is_function_call (c0));
static_assert (is_id_expression (callee_of (c0)));
static_assert (callee_of (c0) != ^^zero_arg);
static_assert (declaration_of (callee_of (c0)) == ^^zero_arg);
static_assert (operands_of (c0).empty ());

// 1: int b = one_arg (x);
constexpr info c1 = initializers_of (statements_of (body_of (^^calls_body))[1])[0];
static_assert (is_function_call (c1));
static_assert (is_id_expression (callee_of (c1)));
static_assert (declaration_of (callee_of (c1)) == ^^one_arg);
static_assert (operands_of (c1).size () == 1);
static_assert (identifier_of (declaration_of (operands_of (c1)[0])) == "x");

// 2: int c = three_args (x, y, 10);
constexpr info c2 = initializers_of (statements_of (body_of (^^calls_body))[2])[0];
static_assert (is_function_call (c2));
static_assert (is_id_expression (callee_of (c2)));
static_assert (declaration_of (callee_of (c2)) == ^^three_args);
static_assert (operands_of (c2).size () == 3);
static_assert (identifier_of (declaration_of (operands_of (c2)[0])) == "x");
static_assert (identifier_of (declaration_of (operands_of (c2)[1])) == "y");
static_assert (is_literal (operands_of (c2)[2]));

// 3: int m = 1 + max_ref (x, y); (call returning reference inside binary op)
constexpr info add_m = initializers_of (statements_of (body_of (^^calls_body))[3])[0];
static_assert (is_literal (operands_of (add_m)[0]));
constexpr info c3 = is_cast (operands_of (add_m)[1])
		    ? operands_of (operands_of (add_m)[1])[0]
		    : operands_of (add_m)[1];
static_assert (is_function_call (c3));
static_assert (!is_unary_operator (c3));
static_assert (is_id_expression (callee_of (c3)));
static_assert (declaration_of (callee_of (c3)) == ^^max_ref);
static_assert (operands_of (c3).size () == 2);

// Leaf expressions (literals and variables) have no operands.
static_assert (operands_of (operands_of (c2)[0]).empty ());
static_assert (operands_of (operands_of (c2)[2]).empty ());

// 4: int p = fp (x); (indirect call through function pointer)
constexpr info c4 = initializers_of (statements_of (body_of (^^calls_body))[4])[0];
static_assert (is_function_call (c4));
static_assert (is_id_expression (callee_of (c4)));
static_assert (identifier_of (declaration_of (callee_of (c4))) == "fp");
static_assert (operands_of (c4).size () == 1);
static_assert (identifier_of (declaration_of (operands_of (c4)[0])) == "x");

// Call returning class with non-trivial destructor (AGGR_INIT_EXPR).
constexpr info cd = return_operand_of (statements_of (body_of (^^call_d_body))[0]);
static_assert (is_function_call (cd));
static_assert (is_id_expression (callee_of (cd)));
static_assert (operands_of (cd).size () == 2);

// Overloaded prefix ++c and postfix c++ both have 1 operand (the dummy int on
// postfix ++ is excluded), and member call c.add(x) has 1 operand (x).
constexpr info mc0 = expression_of (statements_of (body_of (^^member_calls_body))[0]);
constexpr info mc1 = expression_of (statements_of (body_of (^^member_calls_body))[1]);
constexpr info mc2 = return_operand_of (statements_of (body_of (^^member_calls_body))[2]);

static_assert (is_function_call (mc0) && is_prefix (mc0));
static_assert (operands_of (mc0).size () == 1);
static_assert (is_function_call (mc1) && is_postfix (mc1));
static_assert (operands_of (mc1).size () == 1);
static_assert (is_function_call (mc2));
static_assert (is_id_expression (callee_of (mc2)));
static_assert (operands_of (mc2).size () == 1);
static_assert (identifier_of (declaration_of (operands_of (mc2)[0])) == "x");

// For a member operator call, report the object expression rather than its
// implicit address argument.
constexpr info mo = return_operand_of
  (statements_of (body_of (^^member_operator_body))[0]);
static_assert (is_operator_expression (mo));
static_assert (operands_of (mo).size () == 2);
static_assert (is_id_expression (operands_of (mo)[0]));
static_assert (!is_operator_expression (operands_of (mo)[0]));
static_assert (is_id_expression (operands_of (mo)[1]));
static_assert (identifier_of (declaration_of (operands_of (mo)[0])) == "c");
static_assert (identifier_of (declaration_of (operands_of (mo)[1])) == "x");

// Exception checks: callee_of throws on non-call expressions and non-expressions.
static_assert (can_callee_of (c0));
static_assert (!can_callee_of (add_m));
static_assert (!can_callee_of (operands_of (c2)[2]));
static_assert (!can_callee_of (statements_of (body_of (^^calls_body))[0]));
static_assert (!can_callee_of (body_of (^^calls_body)));
static_assert (!can_callee_of (^^one_arg));
static_assert (!can_callee_of (^^int));
static_assert (!can_callee_of (info{}));

static_assert (!can_operands_of (statements_of (body_of (^^calls_body))[0]));
static_assert (!can_operands_of (body_of (^^calls_body)));
static_assert (!can_operands_of (^^one_arg));
static_assert (!can_operands_of (^^int));
static_assert (!can_operands_of (info{}));
