// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::is_operator_expression and std::meta::expression_operator_of (P4395R0).

#include <meta>

using namespace std::meta;

struct Counter
{
  int v;
  constexpr Counter &operator++ () { ++v; return *this; }
  constexpr Counter operator++ (int) { Counter old = *this; ++v; return old; }
  constexpr Counter operator+ (int x) const { return {v + x}; }
  constexpr Counter operator- (int x) const { return {v - x}; }
  constexpr int operator[] (int i) const { return v + i; }
  constexpr int operator() (int a, int b) const { return v + a + b; }
  constexpr int operator, (int x) const { return v + x; }
};

constexpr int
operators_body (int x, int y, Counter c, bool flag)
{
  // Built-in binary operators
  int a0 = x + y;
  int a1 = x - y;
  int a2 = x * y;
  int a3 = x / y;
  int a4 = x % y;
  bool b0 = x == y;
  bool b1 = x != y;
  bool b2 = x < y;
  bool b3 = x <= y;
  bool b4 = x > y;
  bool b5 = x >= y;
  bool l0 = x && y;
  bool l1 = x || y;
  int bit0 = x & y;
  int bit1 = x | y;
  int bit2 = x ^ y;
  int bit3 = x << y;
  int bit4 = x >> y;
  int com = (++x, y);

  // Built-in unary operators
  int u0 = -x;
  int u1 = +x;
  bool u2 = !flag;
  int u3 = ~x;
  int *p = &x;
  int u4 = *p;
  int u5 = ++x;
  int u6 = x++;
  int u7 = --x;
  int u8 = x--;

  // Overloaded operators in operator syntax
  Counter &oc0 = ++c;
  Counter oc1 = c++;
  Counter oc2 = c + 1;
  Counter oc3 = c - 1;
  int oc4 = c[2];
  int oc5 = c (3, 4);
  int oc6 = (c, 5);

  // Explicit operator function calls (should NOT be operator expressions)
  Counter &expl0 = c.operator++ ();
  Counter expl1 = c.operator+ (1);

  // Non-operators
  int lit = 42;
  int cond = x > 0 ? 1 : 2;

  return a0 + a1;
}

consteval bool
can_expression_operator_of (info r)
{
  try { expression_operator_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
check_operators ()
{
  auto stmts = statements_of (body_of (^^operators_body));

#define CHECK(cond) if (!(cond)) return false

  // Built-in binary arithmetic
  info e_a0 = initializers_of (stmts[0])[0];
  CHECK (is_operator_expression (e_a0));
  CHECK (!is_function_call (e_a0));
  CHECK (expression_operator_of (e_a0) == operators::op_plus);
  CHECK (operands_of (e_a0).size () == 2);

  info e_a1 = initializers_of (stmts[1])[0];
  CHECK (is_operator_expression (e_a1));
  CHECK (expression_operator_of (e_a1) == operators::op_minus);

  info e_a2 = initializers_of (stmts[2])[0];
  CHECK (is_operator_expression (e_a2));
  CHECK (expression_operator_of (e_a2) == operators::op_star);

  info e_a3 = initializers_of (stmts[3])[0];
  CHECK (is_operator_expression (e_a3));
  CHECK (expression_operator_of (e_a3) == operators::op_slash);

  info e_a4 = initializers_of (stmts[4])[0];
  CHECK (is_operator_expression (e_a4));
  CHECK (expression_operator_of (e_a4) == operators::op_percent);

  // Comparisons
  info e_b0 = initializers_of (stmts[5])[0];
  CHECK (is_operator_expression (e_b0));
  CHECK (expression_operator_of (e_b0) == operators::op_equals_equals);

  info e_b1 = initializers_of (stmts[6])[0];
  CHECK (is_operator_expression (e_b1));
  CHECK (expression_operator_of (e_b1) == operators::op_exclamation_equals);

  info e_b2 = initializers_of (stmts[7])[0];
  CHECK (is_operator_expression (e_b2));
  CHECK (expression_operator_of (e_b2) == operators::op_less);

  info e_b3 = initializers_of (stmts[8])[0];
  CHECK (is_operator_expression (e_b3));
  CHECK (expression_operator_of (e_b3) == operators::op_less_equals);

  info e_b4 = initializers_of (stmts[9])[0];
  CHECK (is_operator_expression (e_b4));
  CHECK (expression_operator_of (e_b4) == operators::op_greater);

  info e_b5 = initializers_of (stmts[10])[0];
  CHECK (is_operator_expression (e_b5));
  CHECK (expression_operator_of (e_b5) == operators::op_greater_equals);

  // Logical operators
  info e_l0 = initializers_of (stmts[11])[0];
  CHECK (is_operator_expression (e_l0));
  CHECK (expression_operator_of (e_l0) == operators::op_ampersand_ampersand);

  info e_l1 = initializers_of (stmts[12])[0];
  CHECK (is_operator_expression (e_l1));
  CHECK (expression_operator_of (e_l1) == operators::op_pipe_pipe);

  // Bitwise operators
  info e_bit0 = initializers_of (stmts[13])[0];
  CHECK (is_operator_expression (e_bit0));
  CHECK (expression_operator_of (e_bit0) == operators::op_ampersand);

  info e_bit1 = initializers_of (stmts[14])[0];
  CHECK (is_operator_expression (e_bit1));
  CHECK (expression_operator_of (e_bit1) == operators::op_pipe);

  info e_bit2 = initializers_of (stmts[15])[0];
  CHECK (is_operator_expression (e_bit2));
  CHECK (expression_operator_of (e_bit2) == operators::op_caret);

  info e_bit3 = initializers_of (stmts[16])[0];
  CHECK (is_operator_expression (e_bit3));
  CHECK (expression_operator_of (e_bit3) == operators::op_less_less);

  info e_bit4 = initializers_of (stmts[17])[0];
  CHECK (is_operator_expression (e_bit4));
  CHECK (expression_operator_of (e_bit4) == operators::op_greater_greater);

  // Comma operator
  info e_com = initializers_of (stmts[18])[0];
  CHECK (is_operator_expression (e_com));
  CHECK (expression_operator_of (e_com) == operators::op_comma);

  // Built-in unary operators
  info e_u0 = initializers_of (stmts[19])[0];
  CHECK (is_operator_expression (e_u0));
  CHECK (!is_function_call (e_u0));
  CHECK (expression_operator_of (e_u0) == operators::op_minus);
  CHECK (operands_of (e_u0).size () == 1);

  info e_u1 = initializers_of (stmts[20])[0];
  CHECK (is_operator_expression (e_u1));
  CHECK (expression_operator_of (e_u1) == operators::op_plus);

  info e_u2 = initializers_of (stmts[21])[0];
  CHECK (is_operator_expression (e_u2));
  CHECK (expression_operator_of (e_u2) == operators::op_exclamation);

  info e_u3 = initializers_of (stmts[22])[0];
  CHECK (is_operator_expression (e_u3));
  CHECK (expression_operator_of (e_u3) == operators::op_tilde);

  info e_p = initializers_of (stmts[23])[0];
  CHECK (is_operator_expression (e_p));
  CHECK (expression_operator_of (e_p) == operators::op_ampersand);

  info e_u4 = initializers_of (stmts[24])[0];
  CHECK (is_operator_expression (e_u4));
  CHECK (expression_operator_of (e_u4) == operators::op_star);

  info e_u5 = initializers_of (stmts[25])[0];
  CHECK (is_operator_expression (e_u5));
  CHECK (is_prefix (e_u5));
  CHECK (!is_postfix (e_u5));
  CHECK (expression_operator_of (e_u5) == operators::op_plus_plus);

  info e_u6 = initializers_of (stmts[26])[0];
  CHECK (is_operator_expression (e_u6));
  CHECK (!is_prefix (e_u6));
  CHECK (is_postfix (e_u6));
  CHECK (expression_operator_of (e_u6) == operators::op_plus_plus);

  info e_u7 = initializers_of (stmts[27])[0];
  CHECK (is_operator_expression (e_u7));
  CHECK (is_prefix (e_u7));
  CHECK (!is_postfix (e_u7));
  CHECK (expression_operator_of (e_u7) == operators::op_minus_minus);

  info e_u8 = initializers_of (stmts[28])[0];
  CHECK (is_operator_expression (e_u8));
  CHECK (!is_prefix (e_u8));
  CHECK (is_postfix (e_u8));
  CHECK (expression_operator_of (e_u8) == operators::op_minus_minus);

  // Overloaded operators in operator syntax
  info e_oc0 = initializers_of (stmts[29])[0];
  CHECK (is_operator_expression (e_oc0));
  CHECK (is_function_call (e_oc0));
  CHECK (is_prefix (e_oc0));
  CHECK (!is_postfix (e_oc0));
  CHECK (expression_operator_of (e_oc0) == operators::op_plus_plus);

  info e_oc1 = initializers_of (stmts[30])[0];
  CHECK (is_operator_expression (e_oc1));
  CHECK (is_function_call (e_oc1));
  CHECK (!is_prefix (e_oc1));
  CHECK (is_postfix (e_oc1));
  CHECK (expression_operator_of (e_oc1) == operators::op_plus_plus);

  info e_oc2 = initializers_of (stmts[31])[0];
  CHECK (is_operator_expression (e_oc2));
  CHECK (is_function_call (e_oc2));
  CHECK (expression_operator_of (e_oc2) == operators::op_plus);

  info e_oc3 = initializers_of (stmts[32])[0];
  CHECK (is_operator_expression (e_oc3));
  CHECK (is_function_call (e_oc3));
  CHECK (expression_operator_of (e_oc3) == operators::op_minus);

  info e_oc4 = initializers_of (stmts[33])[0];
  CHECK (is_operator_expression (e_oc4));
  CHECK (is_function_call (e_oc4));
  CHECK (expression_operator_of (e_oc4) == operators::op_square_brackets);

  info e_oc5 = initializers_of (stmts[34])[0];
  CHECK (is_operator_expression (e_oc5));
  CHECK (is_function_call (e_oc5));
  CHECK (expression_operator_of (e_oc5) == operators::op_parentheses);

  info e_oc6 = initializers_of (stmts[35])[0];
  CHECK (is_operator_expression (e_oc6));
  CHECK (is_function_call (e_oc6));
  CHECK (expression_operator_of (e_oc6) == operators::op_comma);

  // Explicit function call syntax: c.operator++() and c.operator+(1)
  info e_expl0 = initializers_of (stmts[36])[0];
  CHECK (is_function_call (e_expl0));
  CHECK (!is_operator_expression (e_expl0));
  CHECK (!can_expression_operator_of (e_expl0));

  info e_expl1 = initializers_of (stmts[37])[0];
  CHECK (is_function_call (e_expl1));
  CHECK (!is_operator_expression (e_expl1));
  CHECK (!can_expression_operator_of (e_expl1));

  // Non-operator expressions and non-expressions
  info e_lit = initializers_of (stmts[38])[0];
  CHECK (!is_operator_expression (e_lit));
  CHECK (!can_expression_operator_of (e_lit));

  info e_cond = initializers_of (stmts[39])[0];
  CHECK (is_conditional_operator (e_cond));
  CHECK (!is_operator_expression (e_cond));
  CHECK (!can_expression_operator_of (e_cond));

  // Statements
  CHECK (!is_operator_expression (stmts[0]));
  CHECK (!can_expression_operator_of (stmts[0]));

#undef CHECK
  return true;
}

static_assert (check_operators ());

// Operator function declaration is not an operator expression
static_assert (!is_operator_expression (^^Counter::operator+));
static_assert (!can_expression_operator_of (^^Counter::operator+));
// operator_of works on operator function declaration, but expression_operator_of does not
static_assert (operator_of (^^Counter::operator+) == operators::op_plus);

// Types, null
static_assert (!is_operator_expression (^^int));
static_assert (!can_expression_operator_of (^^int));
static_assert (!is_operator_expression (info{}));
static_assert (!can_expression_operator_of (info{}));
