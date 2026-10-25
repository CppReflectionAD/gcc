// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::statements_of recursive AST traversal.

#include <meta>

using namespace std::meta;

constexpr int test_if(int x) {
  if (x > 0)
    return x;
  else
    return -x;
}

constexpr int test_while(int x) {
  int sum = 0;
  while (x > 0) {
    sum += x;
    --x;
  }
  return sum;
}

consteval int count_leaves(info node) {
  auto children = statements_of(node);
  if (children.size() == 1 && children[0] == node) {
    return 1;
  }
  int sum = 0;
  for (info child : children) {
    sum += count_leaves(child);
  }
  return sum;
}

consteval bool run_test() {
  int if_leaves = count_leaves(body_of( ^^test_if ));
  if (if_leaves != 3)
    return false;

  int while_leaves = count_leaves(body_of( ^^test_while ));
  if (while_leaves != 11)
    return false;

  return true;
}

static_assert(run_test());
