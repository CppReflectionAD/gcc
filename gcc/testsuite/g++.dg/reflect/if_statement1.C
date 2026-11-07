// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test is_if_statement, and condition_of on an if statement and on the if a
// lowered loop ends with.

#include <meta>
#include <vector>

using namespace std::meta;

constexpr float abs_if(float x) {
  if (x > 0.0f)
    return x;
  return -x;
}

constexpr float abs_if_else(float x) {
  if (x < 0.0f)
    return -x;
  else
    return x;
}

constexpr float relu_return(float x) { return x > 0.0f ? x : 0.0f; }

constexpr float relu_assign(float x) {
  float y = 0.0f;
  y = x > 0.0f ? x : 0.0f;
  return y;
}

constexpr float relu_declare(float x) {
  const float y = x > 0.0f ? x : 0.0f;
  return y;
}

int calls;
void up() { ++calls; }
void down() { --calls; }
void ternary_statement(float x) { x > 0.0f ? up() : down(); }

constexpr float w(float x) {
  float y = x;
  while (y < 10.0f)
    y = y * 2.0f;
  return y;
}

constexpr float dw(float x) {
  float y = x;
  do
    y = y * 2.0f;
  while (y < 10.0f);
  return y;
}

constexpr float f(float x) {
  float y = x;
  for (int i = 0; i < 3; ++i)
    y = y * 2.0f;
  return y;
}

constexpr float w_break(float x) {
  float y = x;
  while (y < 10.0f) {
    if (y > 5.0f)
      break;
    y = y * 2.0f;
  }
  return y;
}

consteval info stmt(info fn, int k) {
  return statements_of(body_of(fn))[k];
}

consteval operators cond_op(info s) {
  return operator_of(condition_of(s));
}

// The if statements in a compound statement and the compound statements
// nested in it, in order.
consteval void collect_ifs(info s, std::vector<info> &r) {
  for (info c : statements_of(s))
    if (is_if_statement(c))
      r.push_back(c);
    else if (is_compound_statement(c))
      collect_ifs(c, r);
}

consteval std::vector<info> ifs_in(info s) {
  std::vector<info> r;
  collect_ifs(s, r);
  return r;
}

// An if statement, and its condition and branches.
static_assert(is_if_statement(stmt(^^abs_if, 0)));
static_assert(is_statement(stmt(^^abs_if, 0)));
static_assert(!is_expression(stmt(^^abs_if, 0)));
static_assert(!is_conditional_operator(stmt(^^abs_if, 0)));
static_assert(cond_op(stmt(^^abs_if, 0)) == operators::op_greater);
static_assert(is_return_statement(true_expression_of(stmt(^^abs_if, 0))));
static_assert(!is_if_statement(stmt(^^abs_if, 1)));

static_assert(is_if_statement(stmt(^^abs_if_else, 0)));
static_assert(cond_op(stmt(^^abs_if_else, 0)) == operators::op_less);
static_assert(is_return_statement(false_expression_of(stmt(^^abs_if_else, 0))));

// A `?:` in a return, an assignment, an initializer or on its own is not an
// if statement, nor is the `?:` itself.
static_assert(!is_if_statement(stmt(^^relu_return, 0)));
static_assert(!is_if_statement(return_operand_of(stmt(^^relu_return, 0))));
static_assert(!is_if_statement(stmt(^^relu_assign, 1)));
static_assert(!is_if_statement(stmt(^^relu_declare, 0)));
static_assert(!is_if_statement(stmt(^^ternary_statement, 0)));

// Not statements at all.
static_assert(!is_if_statement(^^int));
static_assert(!is_if_statement(^^abs_if));
static_assert(!is_if_statement(info{}));

// A loop is lowered to a compound statement ending in
// `if (cond) goto body; else goto exit;`, which is an if statement whose
// condition is the loop's.
static_assert(is_compound_statement(stmt(^^w, 1)));
static_assert(!is_if_statement(stmt(^^w, 1)));
static_assert(ifs_in(stmt(^^w, 1)).size() == 1);
static_assert(cond_op(ifs_in(stmt(^^w, 1))[0]) == operators::op_less);

static_assert(ifs_in(stmt(^^dw, 1)).size() == 1);
static_assert(cond_op(ifs_in(stmt(^^dw, 1))[0]) == operators::op_less);

static_assert(ifs_in(stmt(^^f, 1)).size() == 1);
static_assert(cond_op(ifs_in(stmt(^^f, 1))[0]) == operators::op_less);

// A break is an if too: the break's comes first, then the loop's.
static_assert(ifs_in(stmt(^^w_break, 1)).size() == 2);
static_assert(cond_op(ifs_in(stmt(^^w_break, 1))[0]) == operators::op_greater);
static_assert(cond_op(ifs_in(stmt(^^w_break, 1))[1]) == operators::op_less);

// condition_of still rejects what is neither.
consteval bool rejects_non_conditional() {
  try {
    condition_of(stmt(^^relu_declare, 0));
    return false;
  } catch (const std::meta::exception &) {
  }
  return true;
}
static_assert(rejects_non_conditional());
