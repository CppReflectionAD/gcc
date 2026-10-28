// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

int g_var = 42;

int one(int x) {
  return x + g_var;
}

int caller() {
  return one(10);
}

template <std::meta::info R>
int test_fn() {
  return 1;
}

int main() {
  using namespace std::meta;

  constexpr info fn_entity = ^^one;
  constexpr info call_expr = return_operand_of(statements_of(body_of(^^caller))[0]);
  constexpr info fn_id_expr = callee_of(call_expr);

  // fn_entity is an entity, fn_id_expr is an id-expression
  static_assert(fn_entity != fn_id_expr);

  // Instantiations must be distinct
  constexpr auto p1 = &test_fn<fn_entity>;
  constexpr auto p2 = &test_fn<fn_id_expr>;
  static_assert(p1 != p2);
  if (p1 == p2)
    return 1;

  constexpr info var_entity = ^^g_var;
  constexpr info add_expr = return_operand_of(statements_of(body_of(^^one))[0]);
  constexpr info var_id_expr = operands_of(add_expr)[1];

  static_assert(var_entity != var_id_expr);

  constexpr auto p3 = &test_fn<var_entity>;
  constexpr auto p4 = &test_fn<var_id_expr>;
  static_assert(p3 != p4);
  if (p3 == p4)
    return 2;

  // Check parameter id-expression
  constexpr info parm_id_expr = operands_of(add_expr)[0];
  constexpr info parm_entity = parameters_of(^^one)[0];

  static_assert(parm_entity != parm_id_expr);

  constexpr auto p5 = &test_fn<parm_entity>;
  constexpr auto p6 = &test_fn<parm_id_expr>;
  static_assert(p5 != p6);
  if (p5 == p6)
    return 3;

  if (p1() != 1 || p2() != 1 || p3() != 1 || p4() != 1 || p5() != 1 || p6() != 1)
    return 4;

  return 0;
}
