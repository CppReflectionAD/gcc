// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// source_location_of a reflection of a statement gives the line where the
// statement starts, also when the reflection has been stored or passed to a
// function.  Not yet for a block: GCC keeps only where it ends.

#include <meta>
#include <string_view>

using namespace std::meta;

int sink (int);

int
f (int x)
{
  sink (x);
  if (x)
    sink (1);
  if (x) sink (1); else sink (2);
  ;
  int y = 0;
  using T = int;
  for (int i = 0; i < x; ++i)
    sink (i);
  while (x)
    break;
  do
    sink (3);
  while (0);
  switch (x)
    {
    case 1:
      break;
    }
  if constexpr (true)
    sink (4);
  x = x + y;
  return x;
}

template <typename T>
T
g (T x)
{
  sink (1);
  return x;
}

int
scoped (int x)
{
  if (int y = sink (x))
    sink (y);
  if (int y = sink (x); y > 1)
    sink (y);
  if (x)
    {
      int y = x;
      sink (y);
    }
  return 0;
}

consteval info
st (info fn, int k)
{
  return statements_of (body_of (fn))[k];
}

consteval unsigned
line (info r)
{
  return source_location_of (r).line ();
}

static_assert (source_location_of (st (^^f, 0)).line () == 17);
static_assert (line (st (^^f, 0)) == 17);	// expression statement
static_assert (line (st (^^f, 1)) == 18);	// if
static_assert (line (st (^^f, 2)) == 20);	// if with else
static_assert (line (st (^^f, 3)) == 21);	// null statement
static_assert (line (st (^^f, 4)) == 22);	// declaration
static_assert (line (st (^^f, 5)) == 23);	// alias declaration
static_assert (line (st (^^f, 6)) == 24);	// for
static_assert (line (st (^^f, 7)) == 26);	// while
static_assert (line (st (^^f, 8)) == 28);	// do
static_assert (line (st (^^f, 9)) == 31);	// switch
static_assert (line (st (^^f, 10)) == 36);	// if constexpr
static_assert (line (st (^^f, 11)) == 38);	// assignment
static_assert (line (st (^^f, 12)) == 39);	// return

// The parts of an `if' and a loop.
static_assert (line (statements_of (st (^^f, 1))[1]) == 19);
static_assert (line (statements_of (st (^^f, 2))[2]) == 20);
static_assert (line (statements_of (st (^^f, 8))[0]) == 29);

// In an instantiation of a template.
static_assert (line (st (^^g<int>, 0)) == 46);
static_assert (line (st (^^g<int>, 1)) == 47);

// An `if' that declares a variable, in its init-statement, its condition or a
// block, is in a scope of its own, which starts where the `if' does.
static_assert (line (st (^^scoped, 0)) == 53);
static_assert (line (st (^^scoped, 1)) == 55);
static_assert (line (st (^^scoped, 2)) == 57);
static_assert (line (statements_of (st (^^scoped, 0))[0]) == 53);
static_assert (line (statements_of (st (^^scoped, 1))[0]) == 55);

// Stored in a constexpr variable or a class member.
constexpr info stored = st (^^f, 1);
static_assert (source_location_of (stored).line () == 18);
static_assert (line (stored) == 18);
struct holder { info r; };
constexpr holder h { st (^^f, 12) };
static_assert (line (h.r) == 39);

// The file is this one.
static_assert (std::string_view (source_location_of (st (^^f, 0)).file_name ())
	       == source_location_of (^^f).file_name ());
