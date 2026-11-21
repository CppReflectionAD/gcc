// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-empty-body" }
// A reflection of a statement is still a reflection of the same statement
// when a constexpr variable or a class member holds it, or when it is
// passed to or returned from a function, so it is equal to a fresh
// reflection of that statement.  Unsharing the value used to copy the
// statement, and a copy of an `if constexpr' is a different statement.

#include <meta>
#include <array>

using namespace std::meta;

int sink (int);

void plain_if (int x) { if (x) sink (1); }
void if_else (int x) { if (x) sink (1); else sink (2); }
template <int N> void if_cx () { if constexpr (N) sink (1); if constexpr (N) sink (1); }
void null_stmt () { ; }
void block (int x) { { sink (x); } }

consteval info
st (info fn, int k = 0)
{
  return statements_of (body_of (fn))[k];
}

consteval bool
same (info a, info b)
{
  return a == b;
}

consteval info
id (info r)
{
  return r;
}

struct holder { info a; info b; };

#define CHECK(NAME, FN)							\
  constexpr info NAME = st (FN);					\
  static_assert (NAME == st (FN));					\
  static_assert (st (FN) == NAME);					\
  static_assert (same (st (FN), st (FN)));				\
  static_assert (same (NAME, st (FN)));					\
  static_assert (id (st (FN)) == st (FN));				\
  static_assert (id (NAME) == NAME);					\
  static_assert (holder { st (FN), st (FN) }.a == st (FN));

CHECK (s_plain_if, ^^plain_if)
CHECK (s_if_else, ^^if_else)
CHECK (s_if_cx, ^^if_cx<1>)
CHECK (s_null, ^^null_stmt)
CHECK (s_block, ^^block)

constexpr holder h { st (^^plain_if), st (^^if_cx<1>) };
static_assert (h.a == st (^^plain_if));
static_assert (h.b == st (^^if_cx<1>));
static_assert (h.a != h.b);

// A default member initializer or a default argument is copied where it
// is used.
struct dflt { info i = s_if_cx; };
static_assert (dflt {}.i == s_if_cx);
consteval bool
is_if_cx (info r = s_if_cx)
{
  return r == st (^^if_cx<1>);
}
static_assert (is_if_cx ());
consteval bool
is_plain_if (info r = st (^^plain_if))
{
  return r == s_plain_if;
}
static_assert (is_plain_if ());

constexpr std::array<info, 2> arr { s_plain_if, st (^^if_cx<1>) };
static_assert (arr[0] == st (^^plain_if));
static_assert (arr[1] == s_if_cx);

// Two `if constexpr's that are alike are still two statements.
constexpr info s_if_cx2 = st (^^if_cx<1>, 1);
static_assert (s_if_cx != s_if_cx2);
static_assert (!same (s_if_cx, s_if_cx2));
static_assert (id (s_if_cx) != st (^^if_cx<1>, 1));

static_assert (s_plain_if != s_if_else);
static_assert (s_plain_if != s_null);
static_assert (s_block != s_null);
