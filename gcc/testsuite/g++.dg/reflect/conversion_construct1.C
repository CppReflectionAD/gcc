// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

struct Point2D {
  int x;
  int y;
};

struct Converting {
  int val;
  constexpr Converting(int v) : val(v) {}
};

struct MultiArg {
  int a;
  int b;
  constexpr MultiArg(int x, int y) : a(x), b(y) {}
};

struct DefaultCtor {
  int z;
  DefaultCtor() { z = 42; }
};

Point2D make_point() {
  return Point2D{1, 2};
}

void fn_body(int v) {
  // Conversions (casts and converting constructor)
  double a = static_cast<double>(v);
  double b = v;
  Converting c1 = 100;
  Converting c2(200);

  // Constructions (multi-arg, default, aggregate)
  MultiArg m(1, 2);
  DefaultCtor d = DefaultCtor();
  Point2D p{3, 4};

  // Function call returning class by value
  Point2D pt = make_point();

  // Plain variable and operator
  int x = 1;
  int y = x + 2;
}

consteval bool test_conversions_and_constructs() {
  using namespace std::meta;

  auto stmts = statements_of(body_of(^^fn_body));

  // 0: double a = static_cast<double>(v);
  info init_a = initializers_of(stmts[0])[0];
  if (!is_conversion(init_a)) return false;
  if (!is_cast(init_a)) return false; // is_cast is alias for is_conversion
  if (is_construct(init_a)) return false;
  if (operands_of(init_a).size() != 1) return false;

  // 1: double b = v; (implicit conversion int -> double)
  info init_b = initializers_of(stmts[1])[0];
  if (!is_conversion(init_b)) return false;
  if (is_construct(init_b)) return false;
  if (operands_of(init_b).size() != 1) return false;

  // 2: Converting c1 = 100; (converting constructor: both is_conversion and is_construct)
  info init_c1 = initializers_of(stmts[2])[0];
  if (!is_conversion(init_c1)) return false;
  if (!is_construct(init_c1)) return false;
  if (operands_of(init_c1).size() != 1) return false;
  if (!is_literal(operands_of(init_c1)[0])) return false;

  // 3: Converting c2(200); (direct-init converting constructor: both is_conversion and is_construct)
  info init_c2 = initializers_of(stmts[3])[0];
  if (!is_conversion(init_c2)) return false;
  if (!is_construct(init_c2)) return false;
  if (operands_of(init_c2).size() != 1) return false;
  if (!is_literal(operands_of(init_c2)[0])) return false;

  // 4: MultiArg m(1, 2); (multi-arg construction: is_construct true, is_conversion false)
  info init_m = initializers_of(stmts[4])[0];
  if (is_conversion(init_m)) return false;
  if (!is_construct(init_m)) return false;
  if (operands_of(init_m).size() != 2) return false;

  // 5: DefaultCtor d = DefaultCtor(); (default construction: is_construct true, is_conversion false)
  info init_d = initializers_of(stmts[5])[0];
  if (is_conversion(init_d)) return false;
  if (!is_construct(init_d)) return false;
  if (operands_of(init_d).size() != 0) return false;

  // 6: Point2D p{3, 4}; (aggregate init: is_construct true, is_conversion false)
  info init_p = initializers_of(stmts[6])[0];
  if (is_conversion(init_p)) return false;
  if (!is_construct(init_p)) return false;
  if (operands_of(init_p).size() != 2) return false;

  // 7: Point2D pt = make_point(); (call returning class: is_function_call true, is_construct false)
  info init_pt = initializers_of(stmts[7])[0];
  if (!is_function_call(init_pt)) return false;
  if (is_construct(init_pt)) return false;
  if (is_conversion(init_pt)) return false;

  // 8: int x = 1; (literal: neither construct nor conversion)
  info init_x = initializers_of(stmts[8])[0];
  if (is_conversion(init_x)) return false;
  if (is_construct(init_x)) return false;

  // 9: int y = x + 2; (binary operator: neither construct nor conversion)
  info init_y = initializers_of(stmts[9])[0];
  if (is_conversion(init_y)) return false;
  if (is_construct(init_y)) return false;
  if (!is_operator_expression(init_y)) return false;

  // Non-expressions
  if (is_conversion(^^int)) return false;
  if (is_construct(^^int)) return false;
  if (is_conversion(^^make_point)) return false;
  if (is_construct(^^make_point)) return false;
  if (is_conversion(info{})) return false;
  if (is_construct(info{})) return false;

  return true;
}

static_assert(test_conversions_and_constructs());
