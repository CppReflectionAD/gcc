// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A reflection of a statement can name a specialization that is never
// emitted, as with clang: the specialization isn't dependent.  It was an ICE
// for a null statement or an alias declaration (cpp_reflection_ad#284), and
// a block was taken for a statement-expression, so the specialization was
// dependent and couldn't be used (cpp_reflection_ad#285).

#include <meta>

using namespace std::meta;

int sink (int);

int
f (int x)
{
  ;
  using T = int;
  {
    sink (x);
  }
  if (x)
    sink (1);
  sink (x);
  T y = x;
  return y;
}

consteval info
st (int k)
{
  return statements_of (body_of (^^f))[k];
}

template <info R> struct tmpl { using type = int; };

#define CHECK(K)						\
  using A##K = tmpl<st (K)>;					\
  static_assert (__is_same (typename tmpl<st (K)>::type, int));	\
  static_assert (__is_same (tmpl<st (K)>, tmpl<st (K)>));

CHECK (0)	// null statement
CHECK (1)	// alias declaration
CHECK (2)	// block
CHECK (3)	// if
CHECK (4)	// expression statement
CHECK (5)	// declaration
CHECK (6)	// return

static_assert (!__is_same (tmpl<st (3)>, tmpl<st (6)>));
static_assert (!__is_same (tmpl<st (2)>, tmpl<st (4)>));
