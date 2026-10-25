// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -g -O2" }
// Test std::meta::statements_of when debug information (-g) is enabled.
// Verifies that internal DEBUG_BEGIN_STMT markers are not returned as statements.

#include <meta>

using namespace std::meta;

constexpr int helper(int a) { return a * 2; }

constexpr int test_func(int x) {
  int v = helper(x);
  return v;
}

constexpr int test_multi_func(int x) {
  int a = helper(x);
  int b = helper(a);
  return b;
}

consteval bool test_statements() {
  auto stmts = statements_of(body_of(^^test_func));
  if (stmts.size() != 2) return false;
  if (!is_declaration_statement(stmts[0])) return false;
  if (!is_return_statement(stmts[1])) return false;

  auto multi_stmts = statements_of(body_of(^^test_multi_func));
  if (multi_stmts.size() != 3) return false;
  if (!is_declaration_statement(multi_stmts[0])) return false;
  if (!is_declaration_statement(multi_stmts[1])) return false;
  if (!is_return_statement(multi_stmts[2])) return false;

  return true;
}

static_assert(test_statements());
