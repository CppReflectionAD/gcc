// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::initializer_of on the locals that follow a local of a
// class with a non-trivial destructor.

#include <meta>
#include <type_traits>

using namespace std::meta;

struct T { double v; };
struct D { double v; ~D () {} };

static_assert (std::is_trivially_destructible_v<T>);
static_assert (!std::is_trivially_destructible_v<D>);

T make_t (double x) { return {x}; }
D make_d (double x) { return {x}; }

double two_t (double x) { T a = make_t (x); T b = make_t (a.v); return b.v; }
double two_d (double x) { D a = make_d (x); D b = make_d (a.v); return b.v; }
double three_d (double x)
{
  D a = make_d (x);
  D b = make_d (a.v);
  D c = make_d (b.v);
  return c.v;
}

// initializer_of throws if a local has no initializer.
consteval bool
every_local_has_initializer (info fn)
{
  for (info s : statements_of (body_of (fn)))
    if (is_declaration_statement (s))
      (void) initializer_of (declared_variable_of (s));
  return true;
}

static_assert (every_local_has_initializer (^^two_t));
static_assert (every_local_has_initializer (^^two_d));
static_assert (every_local_has_initializer (^^three_d));
