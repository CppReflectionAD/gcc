// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A temporary bound to a reference in an immediate function context is
// initialized when the function is evaluated, not where it is defined, so a
// reflection query in its initializer sees what is declared before the call.

#include <meta>
#include <vector>

using namespace std::meta;

namespace reg {}
struct S;

constexpr access_context uctx = access_context::unchecked ();

consteval std::size_t
range_for ()
{
  std::size_t n = 0;
  for (info r : members_of (^^reg, uctx))
    n += is_type (r);
  return n;
}

consteval std::size_t
rvalue_ref ()
{
  auto &&ms = members_of (^^reg, uctx);
  return ms.size ();
}

consteval std::size_t
const_ref ()
{
  const auto &ms = members_of (^^reg, uctx);
  return ms.size ();
}

consteval std::vector<info>
wrap ()
{
  return members_of (^^reg, uctx);
}

consteval std::size_t
through_call ()
{
  auto &&ms = wrap ();
  return ms.size ();
}

consteval bool
complete ()
{
  const bool &b = is_complete_type (^^S);
  return b;
}

constexpr std::size_t
consteval_if ()
{
  if consteval
    {
      auto &&ms = members_of (^^reg, uctx);
      return ms.size ();
    }
  return 99;
}

template <typename T>
consteval std::size_t
instantiated_early ()
{
  auto &&ms = members_of (^^reg, uctx);
  return ms.size ();
}
// Instantiated, and evaluated, before reg::A is declared.
static_assert (instantiated_early<int> () == 0);

// Not an immediate function context: the call is an immediate invocation,
// evaluated where it is written, before S is defined.
constexpr bool
not_immediate ()
{
  const bool &b = is_complete_type (^^S);
  return b;
}

// A static constexpr reference's initializer is manifestly constant-evaluated
// where it is written.
consteval int
static_constexpr ()
{
  static constexpr const int &r = 42;
  return r;
}

consteval bool
static_constexpr_query ()
{
  static constexpr const bool &b = is_complete_type (^^S);
  return b;
}

namespace reg {
struct A {};
}
struct S {};

static_assert (range_for () == 1);
static_assert (rvalue_ref () == 1);
static_assert (const_ref () == 1);
static_assert (through_call () == 1);
static_assert (complete ());
static_assert (consteval_if () == 1);
static_assert (instantiated_early<int> () == 1);
static_assert (!not_immediate ());
static_assert (static_constexpr () == 42);
static_assert (!static_constexpr_query ());
