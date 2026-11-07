// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Using a label reflection as a template argument must produce a diagnostic
// rather than an ICE.

#include <meta>

using namespace std::meta;

template <info L> constexpr int lab = 1; // { dg-error "a reflection of a label cannot be used as a template argument" }

int jumps(int x) {
again:
  if (x++ < 3)
    goto again;
  return x;
}

constexpr info a = label_of(statements_of(body_of(^^jumps))[0]);
const int *p = &lab<a>;
