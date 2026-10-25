// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::is_expression_statement and std::meta::expression_of.

#include <meta>

using namespace std::meta;

constexpr void sink (int) {}

struct D {
  int v;
  constexpr ~D () {}
};

constexpr D make_d (int x) { return {x}; }

constexpr int
test_fn (int x)
{
  int a = 0;
  int b = 0;
  a = x + 1;
  a += 2;
  ++a;
  a++;
  sink (a);
  a = 3, b = 4;
  make_d (a);
  if (x > 0)
    a = x;
  else
    a = -x;
  return a + b;
}

consteval bool
check_expr_stmt (info s)
{
  if (!is_statement (s))
    return false;
  if (!is_expression_statement (s))
    return false;
  if (is_expression (s))
    return false;
  if (is_compound_statement (s))
    return false;
  if (is_declaration_statement (s))
    return false;
  if (is_return_statement (s))
    return false;

  info e = expression_of (s);
  if (!is_expression (e))
    return false;
  if (is_statement (e))
    return false;
  if (is_expression_statement (e))
    return false;
  return true;
}

consteval bool
test_expr_statements ()
{
  info body = body_of (^^test_fn);
  auto stmts = statements_of (body);
  // 0: int a = 0;
  // 1: int b = 0;
  // 2: a = x + 1;
  // 3: a += 2;
  // 4: ++a;
  // 5: a++;
  // 6: sink (a);
  // 7: a = 3, b = 4;
  // 8: make_d (a);
  // 9: if (x > 0) a = x; else a = -x;
  // 10: return a + b;
  if (stmts.size () != 11)
    return false;

  // Declarations are not expression statements.
  if (is_expression_statement (stmts[0]) || is_expression_statement (stmts[1]))
    return false;

  // 2: a = x + 1;
  if (!check_expr_stmt (stmts[2]))
    return false;
  info e2 = expression_of (stmts[2]);
  if (!is_binary_operator (e2) || operator_of (e2) != operators::op_equals)
    return false;
  auto ops2 = operands_of (e2);
  if (ops2.size () != 2 || !is_variable (ops2[0]) || !is_binary_operator (ops2[1]))
    return false;

  // 3: a += 2;
  if (!check_expr_stmt (stmts[3]))
    return false;
  info e3 = expression_of (stmts[3]);
  if (!is_binary_operator (e3))
    return false;

  // 4: ++a;
  if (!check_expr_stmt (stmts[4]))
    return false;
  info e4 = expression_of (stmts[4]);
  if (!is_unary_operator (e4) || operator_of (e4) != operators::op_plus_plus)
    return false;
  if (operands_of (e4).size () != 1 || !is_variable (operands_of (e4)[0]))
    return false;

  // 5: a++;
  if (!check_expr_stmt (stmts[5]))
    return false;
  info e5 = expression_of (stmts[5]);
  if (!is_unary_operator (e5) || operator_of (e5) != operators::op_plus_plus)
    return false;
  if (operands_of (e5).size () != 1 || !is_variable (operands_of (e5)[0]))
    return false;

  // 6: sink (a);
  if (!check_expr_stmt (stmts[6]))
    return false;
  info e6 = expression_of (stmts[6]);
  if (!is_function_call (e6) || callee_of (e6) != ^^sink)
    return false;

  // 7: a = 3, b = 4;
  if (!check_expr_stmt (stmts[7]))
    return false;
  info e7 = expression_of (stmts[7]);
  if (!is_binary_operator (e7) || operator_of (e7) != operators::op_comma)
    return false;
  auto ops7 = operands_of (e7);
  if (ops7.size () != 2
      || !is_binary_operator (ops7[0])
      || !is_binary_operator (ops7[1]))
    return false;

  // 8: make_d (a); (non-trivial destructor temporary)
  if (!check_expr_stmt (stmts[8]))
    return false;
  info e8 = expression_of (stmts[8]);
  if (!is_function_call (e8) || callee_of (e8) != ^^make_d)
    return false;

  // 9: if (x > 0) a = x; else a = -x;
  if (is_expression_statement (stmts[9]))
    return false;
  auto branches = statements_of (stmts[9]);
  if (branches.size () != 3)
    return false;
  if (!check_expr_stmt (branches[1]) || !check_expr_stmt (branches[2]))
    return false;
  if (operator_of (expression_of (branches[1])) != operators::op_equals)
    return false;
  if (operator_of (expression_of (branches[2])) != operators::op_equals)
    return false;

  // 10: return a + b;
  if (is_expression_statement (stmts[10]))
    return false;

  // Non-statement reflections.
  if (is_expression_statement (body))
    return false;
  if (is_expression_statement (^^int))
    return false;
  if (is_expression_statement (^^test_fn))
    return false;
  if (is_expression_statement (info{}))
    return false;

  return true;
}

consteval bool
throws_expression_of (info r)
{
  try
    {
      expression_of (r);
      return false;
    }
  catch (std::meta::exception &)
    {
      return true;
    }
}

consteval bool
test_exceptions ()
{
  info body = body_of (^^test_fn);
  auto stmts = statements_of (body);
  info expr = expression_of (stmts[2]);

  return throws_expression_of (body)
	 && throws_expression_of (stmts[0])
	 && throws_expression_of (stmts[9])
	 && throws_expression_of (stmts[10])
	 && throws_expression_of (expr)
	 && throws_expression_of (^^int)
	 && throws_expression_of (^^test_fn)
	 && throws_expression_of (info{});
}

static_assert (test_expr_statements ());
static_assert (test_exceptions ());
