// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Two reflections of compound statements are equal only if they reflect the
// same block, even if the blocks are alike.  Comparing two that are alike
// used to be an internal compiler error.

#include <meta>

using namespace std::meta;

double f (double x) { x + 1; return x; }
double g (double x) { x + 1; return x; }
double h (double x) { return x; }
double k (double x) { return x; }
double l (double x) { { int a = 0; } { int a = 0; } return x; }

consteval info
stmt (info fn, unsigned i)
{
  return statements_of (body_of (fn))[i];
}

consteval unsigned
count (info s)
{
  return statements_of (s).size ();
}

static_assert (body_of (^^f) == body_of (^^f));
static_assert (body_of (^^f) != body_of (^^g));
static_assert (body_of (^^f) != body_of (^^h));
static_assert (body_of (^^h) == body_of (^^h));
static_assert (body_of (^^h) != body_of (^^k));

// A constexpr call is looked up by its arguments, so this compares the bodies.
static_assert (count (body_of (^^f)) == 2);
static_assert (count (body_of (^^g)) == 2);

static_assert (stmt (^^l, 0) == stmt (^^l, 0));
static_assert (stmt (^^l, 0) != stmt (^^l, 1));
static_assert (count (stmt (^^l, 0)) == 1);
static_assert (count (stmt (^^l, 1)) == 1);

// A block isn't equal to a statement in it.
static_assert (body_of (^^f) != stmt (^^f, 0));
static_assert (body_of (^^h) != stmt (^^h, 0));
