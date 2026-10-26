// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

enum class Color { Red, Green, Blue };

int global_var = 10;

int dummy_fn(int a, int b) {
  int local_var = a + b;
  int g = global_var;
  return local_var;
}

consteval bool test_id_expressions() {
  using namespace std::meta;

  auto stmts = statements_of(body_of(^^dummy_fn));

  // 0: int local_var = a + b;
  info init_local = initializers_of(stmts[0])[0];
  if (is_id_expression(init_local)) return false; // a + b is an operator expression

  auto add_ops = operands_of(init_local);
  if (add_ops.size() != 2) return false;

  // add_ops[0] is parameter a
  info op_a = add_ops[0];
  if (!is_id_expression(op_a)) return false;
  if (!is_variable_reference(op_a)) return false;
  if (!is_variable(op_a)) return false;
  if (identifier_of(declaration_of(op_a)) != "a") return false;

  // add_ops[1] is parameter b
  info op_b = add_ops[1];
  if (!is_id_expression(op_b)) return false;
  if (!is_variable_reference(op_b)) return false;
  if (identifier_of(declaration_of(op_b)) != "b") return false;

  // 1: int g = global_var;
  info init_g = initializers_of(stmts[1])[0];
  if (!is_id_expression(init_g)) return false;
  if (!is_variable_reference(init_g)) return false;
  if (identifier_of(declaration_of(init_g)) != "global_var") return false;

  // 2: return local_var;
  info ret_stmt = stmts[2];
  if (!is_return_statement(ret_stmt)) return false;
  info ret_op = return_operand_of(ret_stmt);
  if (!is_id_expression(ret_op)) return false;
  if (!is_variable_reference(ret_op)) return false;
  if (identifier_of(declaration_of(ret_op)) != "local_var") return false;

  // Entity and parameter reflections are not identifier expressions.
  if (is_id_expression(^^global_var)) return false;
  if (is_id_expression(parameters_of(^^dummy_fn)[0])) return false;

  // Non-id-expressions
  if (is_id_expression(init_local)) return false; // binary op
  if (is_id_expression(^^int)) return false;      // type
  if (is_id_expression(^^dummy_fn)) return false; // function
  if (is_id_expression(info{})) return false;     // null
  if (is_id_expression(ret_stmt)) return false;   // statement

  return true;
}

static_assert(test_id_expressions());
