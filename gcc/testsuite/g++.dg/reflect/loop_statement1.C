// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection" }
// Test Option 2 loop reflection metafunctions and then_statement_of /
// else_statement_of.

#include <meta>
#include <cassert>

using namespace std::meta;

struct S {
  static inline int dtors = 0;
  int v = 0;
  constexpr S(int x = 0) : v(x) {}
  constexpr ~S() { if !consteval { ++dtors; } }
  constexpr bool ok() const { return v < 3; }
};

int f_for_compound(int x) {
  for (int i = 0; i < 4; ++i) {
    if (i == 1)
      continue;
    if (i == 3)
      break;
    x += i;
  }
  return x;
}

int f_for_single(int x) {
  for (x = 1; x < 5; ++x)
    x += 1;
  return x;
}

void f_for_empty_and_null() {
  for (;;) {}
  for (; ; ) ;
  for (int a = 0, b = 1; a < b; ++a) {}
}

int f_for_dtor() {
  int sum = 0;
  for (S s(0); s.ok(); ++s.v) {
    sum += s.v;
  }
  return sum;
}

int f_while(int x) {
  while (x < 10) {
    if (x == 5)
      break;
    ++x;
  }
  while (x < 20)
    ++x;
  return x;
}

int f_do(int x) {
  do {
    ++x;
  } while (x < 5);
  do
    ++x;
  while (x < 10);
  return x;
}

template <typename T>
T f_tmpl(T x) {
  for (T i = 0; i < 3; ++i) {
    x += i;
  }
  while (x < 10)
    ++x;
  do {
    ++x;
  } while (x < 12);
  return x;
}

int f_if(int x) {
  if (x > 0) {
    return x;
  } else {
    return -x;
  }
}

int f_if_no_else(int x) {
  if (x > 0)
    return x;
  if (x < 0) {}
  return 0;
}

consteval info stmt(info fn, int k) {
  return statements_of(body_of(fn))[k];
}

// f_for_compound
constexpr info for1 = stmt(^^f_for_compound, 0);
static_assert(is_statement(for1));
static_assert(is_for_statement(for1));
static_assert(!is_while_statement(for1));
static_assert(!is_do_statement(for1));
static_assert(!is_if_statement(for1));
static_assert(is_declaration_statement(init_statement_of(for1)));
static_assert(identifier_of(declared_variable_of(init_statement_of(for1))) == "i");
static_assert(is_binary_operator(condition_of(for1)));
static_assert(operator_of(condition_of(for1)) == op_less);
static_assert(is_unary_operator(increment_of(for1)));
static_assert(operator_of(increment_of(for1)) == op_plus_plus);
static_assert(is_compound_statement(loop_body_of(for1)));
static_assert(loop_body_of(for1) == loop_body_of(for1));
static_assert(statements_of(loop_body_of(for1)).size() == 3);
static_assert(is_if_statement(statements_of(loop_body_of(for1))[0]));
static_assert(is_continue_statement(then_statement_of(statements_of(loop_body_of(for1))[0])));
static_assert(else_statement_of(statements_of(loop_body_of(for1))[0]) == info{});
static_assert(is_break_statement(then_statement_of(statements_of(loop_body_of(for1))[1])));

// f_for_single: expr init and non-compound body
constexpr info for2 = stmt(^^f_for_single, 0);
static_assert(is_for_statement(for2));
static_assert(is_expression_statement(init_statement_of(for2)));
static_assert(is_binary_operator(expression_of(init_statement_of(for2))));
static_assert(is_binary_operator(condition_of(for2)));
static_assert(is_unary_operator(increment_of(for2)));
static_assert(!is_compound_statement(loop_body_of(for2)));
static_assert(is_expression_statement(loop_body_of(for2)));

// f_for_empty_and_null
constexpr info for_empty = stmt(^^f_for_empty_and_null, 0);
static_assert(is_for_statement(for_empty));
static_assert(init_statement_of(for_empty) == info{});
static_assert(condition_of(for_empty) == info{});
static_assert(increment_of(for_empty) == info{});
static_assert(is_compound_statement(loop_body_of(for_empty)));
static_assert(loop_body_of(for_empty) == loop_body_of(for_empty));
static_assert(statements_of(loop_body_of(for_empty)).empty());

constexpr info for_null = stmt(^^f_for_empty_and_null, 1);
static_assert(is_for_statement(for_null));
static_assert(init_statement_of(for_null) == info{});
static_assert(condition_of(for_null) == info{});
static_assert(increment_of(for_null) == info{});
static_assert(!is_compound_statement(loop_body_of(for_null)));
static_assert(is_expression_statement(loop_body_of(for_null)));

constexpr info for_multi = stmt(^^f_for_empty_and_null, 2);
static_assert(is_for_statement(for_multi));
static_assert(is_declaration_statement(init_statement_of(for_multi)));
static_assert(declarators_of(init_statement_of(for_multi)).size() == 2);

// f_for_dtor: init var with non-trivial destructor
constexpr info for_dtor = stmt(^^f_for_dtor, 1);
static_assert(is_for_statement(for_dtor));
static_assert(is_declaration_statement(init_statement_of(for_dtor)));
static_assert(identifier_of(declared_variable_of(init_statement_of(for_dtor))) == "s");
static_assert(is_compound_statement(loop_body_of(for_dtor)));
static_assert(loop_body_of(for_dtor) == loop_body_of(for_dtor));
static_assert(statements_of(loop_body_of(for_dtor)).size() == 1);

// f_while
constexpr info w1 = stmt(^^f_while, 0);
static_assert(is_while_statement(w1));
static_assert(is_binary_operator(condition_of(w1)));
static_assert(is_compound_statement(loop_body_of(w1)));
static_assert(statements_of(loop_body_of(w1)).size() == 2);

constexpr info w2 = stmt(^^f_while, 1);
static_assert(is_while_statement(w2));
static_assert(!is_compound_statement(loop_body_of(w2)));
static_assert(is_expression_statement(loop_body_of(w2)));

// f_do
constexpr info d1 = stmt(^^f_do, 0);
static_assert(is_do_statement(d1));
static_assert(is_binary_operator(condition_of(d1)));
static_assert(is_compound_statement(loop_body_of(d1)));
static_assert(loop_body_of(d1) == loop_body_of(d1));

constexpr info d2 = stmt(^^f_do, 1);
static_assert(is_do_statement(d2));
static_assert(!is_compound_statement(loop_body_of(d2)));
static_assert(is_expression_statement(loop_body_of(d2)));

// Template instantiation
constexpr info t_for = stmt(^^f_tmpl<int>, 0);
constexpr info t_while = stmt(^^f_tmpl<int>, 1);
constexpr info t_do = stmt(^^f_tmpl<int>, 2);
static_assert(is_for_statement(t_for));
static_assert(is_compound_statement(loop_body_of(t_for)));
static_assert(is_while_statement(t_while));
static_assert(!is_compound_statement(loop_body_of(t_while)));
static_assert(is_do_statement(t_do));
static_assert(is_compound_statement(loop_body_of(t_do)));

// if then/else statements
constexpr info if1 = stmt(^^f_if, 0);
static_assert(is_if_statement(if1));
static_assert(is_return_statement(then_statement_of(if1)));
static_assert(is_return_statement(else_statement_of(if1)));
static_assert(then_statement_of(if1) == then_statement_of(if1));
static_assert(else_statement_of(if1) == else_statement_of(if1));

constexpr info if2 = stmt(^^f_if_no_else, 0);
static_assert(is_return_statement(then_statement_of(if2)));
static_assert(else_statement_of(if2) == info{});

constexpr info if3 = stmt(^^f_if_no_else, 1);
static_assert(is_compound_statement(then_statement_of(if3)));
static_assert(then_statement_of(if3) == then_statement_of(if3));
static_assert(statements_of(then_statement_of(if3)).empty());
static_assert(else_statement_of(if3) == info{});

consteval bool rejects_invalid() {
  try {
    init_statement_of(w1);
    return false;
  } catch (std::meta::exception &) {}
  try {
    increment_of(w1);
    return false;
  } catch (std::meta::exception &) {}
  try {
    loop_body_of(if1);
    return false;
  } catch (std::meta::exception &) {}
  try {
    then_statement_of(w1);
    return false;
  } catch (std::meta::exception &) {}
  try {
    else_statement_of(w1);
    return false;
  } catch (std::meta::exception &) {}
  return true;
}
static_assert(rejects_invalid());

int main() {
  assert(f_for_compound(0) == 2);
  assert(f_for_single(0) == 5);
  assert(f_for_dtor() == 3);
  assert(S::dtors == 1);
  assert(f_while(0) == 20);
  assert(f_do(0) == 10);
  assert(f_tmpl(0) == 12);
  assert(f_if(-5) == 5);
  return 0;
}
