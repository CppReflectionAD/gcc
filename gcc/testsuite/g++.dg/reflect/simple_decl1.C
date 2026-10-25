// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::is_simple_declaration, std::meta::declarators_of,
// and std::meta::initializers_of (P4395R0).

#include <meta>

using namespace std::meta;

constexpr double
initialized_local (double x)
{
  double a = 2.0 * x;
  return a + x;
}

constexpr int
uninitialized_then_assigned (int x)
{
  int u;
  u = x + 1;
  return u;
}

constexpr int
multi_declarator (int x)
{
  int a = 1, b, c = a + x;
  b = c;
  return b;
}

constexpr double
cast_initializer (int x)
{
  double d = static_cast<double> (x);
  return d;
}

void destroyed (double);
struct D { double v; ~D () { destroyed (v); } };
D make_d (double x) { return {x}; }
double d_local (double x) { D a = make_d (x); return a.v; }

consteval bool
can_declarators_of (info r)
{
  try { declarators_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
can_initializers_of (info r)
{
  try { initializers_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
can_declared_variable_of (info r)
{
  try { declared_variable_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

consteval bool
can_initializer_of (info r)
{
  try { initializer_of (r); }
  catch (std::meta::exception &) { return false; }
  return true;
}

// Initialized local variable (`double a = 2.0 * x;`).
constexpr info s_init = statements_of (body_of (^^initialized_local))[0];
static_assert (is_statement (s_init));
static_assert (is_declaration_statement (s_init));
static_assert (is_simple_declaration (s_init));
static_assert (!is_expression_statement (s_init));
static_assert (!is_return_statement (s_init));
static_assert (!is_compound_statement (s_init));

static_assert (declarators_of (s_init).size () == 1);
static_assert (initializers_of (s_init).size () == 1);
static_assert (declarators_of (s_init)[0] == declared_variable_of (s_init));
static_assert (is_variable (declarators_of (s_init)[0]));
static_assert (identifier_of (declarators_of (s_init)[0]) == "a");
static_assert (type_of (declarators_of (s_init)[0]) == ^^double);

constexpr info init_a = initializers_of (s_init)[0];
static_assert (init_a != info{});
static_assert (init_a == initializer_of (declarators_of (s_init)[0]));
static_assert (init_a == initializer_of (s_init));
static_assert (is_expression (init_a));
static_assert (is_binary_operator (init_a));
static_assert (operator_of (init_a) == operators::op_star);

// Uninitialized variable followed by assignment (`int u; u = x + 1;`).
constexpr info s_uninit = statements_of (body_of (^^uninitialized_then_assigned))[0];
constexpr info s_assign = statements_of (body_of (^^uninitialized_then_assigned))[1];
static_assert (is_declaration_statement (s_uninit));
static_assert (is_simple_declaration (s_uninit));
static_assert (declarators_of (s_uninit).size () == 1);
static_assert (identifier_of (declarators_of (s_uninit)[0]) == "u");
static_assert (initializers_of (s_uninit).size () == 1);
static_assert (initializers_of (s_uninit)[0] == info{});
static_assert (initializer_of (declarators_of (s_uninit)[0]) == info{});
static_assert (initializer_of (s_uninit) == info{});

static_assert (is_expression_statement (s_assign));
static_assert (!is_declaration_statement (s_assign));
static_assert (!is_simple_declaration (s_assign));

// Multiple declarators (`int a = 1, b, c = a + x;`).
constexpr info m0 = statements_of (body_of (^^multi_declarator))[0];
constexpr info m1 = statements_of (body_of (^^multi_declarator))[1];
constexpr info m2 = statements_of (body_of (^^multi_declarator))[2];
static_assert (is_simple_declaration (m0));
static_assert (is_simple_declaration (m1));
static_assert (is_simple_declaration (m2));
static_assert (identifier_of (declarators_of (m0)[0]) == "a");
static_assert (identifier_of (declarators_of (m1)[0]) == "b");
static_assert (identifier_of (declarators_of (m2)[0]) == "c");
static_assert (is_literal (initializers_of (m0)[0]));
static_assert (initializers_of (m1)[0] == info{});
static_assert (is_binary_operator (initializers_of (m2)[0]));
static_assert (operator_of (initializers_of (m2)[0]) == operators::op_plus);

// Cast in initializer is preserved.
constexpr info s_cast = statements_of (body_of (^^cast_initializer))[0];
static_assert (is_simple_declaration (s_cast));
static_assert (is_cast (initializers_of (s_cast)[0]));

// Class with non-trivial destructor initialized by call.
constexpr info s_d = statements_of (body_of (^^d_local))[0];
static_assert (is_simple_declaration (s_d));
static_assert (identifier_of (declarators_of (s_d)[0]) == "a");
static_assert (is_function_call (initializers_of (s_d)[0]));
static_assert (callee_of (initializers_of (s_d)[0]) == ^^make_d);

// Negative cases and exception checks.
constexpr info s_ret = statements_of (body_of (^^initialized_local))[1];
static_assert (!is_simple_declaration (info{}));
static_assert (!is_simple_declaration (^^int));
static_assert (!is_simple_declaration (^^initialized_local));
static_assert (!is_simple_declaration (body_of (^^initialized_local)));
static_assert (!is_simple_declaration (s_ret));
static_assert (!is_simple_declaration (s_assign));
static_assert (!is_simple_declaration (declarators_of (s_init)[0]));

static_assert (can_declarators_of (s_init));
static_assert (can_initializers_of (s_init));
static_assert (!can_declarators_of (info{}));
static_assert (!can_declarators_of (^^int));
static_assert (!can_declarators_of (body_of (^^initialized_local)));
static_assert (!can_declarators_of (s_ret));
static_assert (!can_declarators_of (s_assign));
static_assert (!can_declarators_of (declarators_of (s_init)[0]));

static_assert (!can_initializers_of (info{}));
static_assert (!can_initializers_of (^^int));
static_assert (!can_initializers_of (body_of (^^initialized_local)));
static_assert (!can_initializers_of (s_ret));
static_assert (!can_initializers_of (s_assign));
static_assert (!can_initializers_of (declarators_of (s_init)[0]));

static_assert (!can_declared_variable_of (info{}));
static_assert (!can_declared_variable_of (^^int));
static_assert (!can_declared_variable_of (declarators_of (s_init)[0]));
static_assert (!can_initializer_of (info{}));
static_assert (!can_initializer_of (^^int));
static_assert (!can_initializer_of (s_ret));
