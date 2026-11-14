// { dg-do compile { target c++20 } }
// { dg-options "-fno-delete-null-pointer-checks" }
// The address of an object or function is never null in a constant
// expression, even when -fno-delete-null-pointer-checks (implied by
// -fsanitize=null, nonnull-attribute and returns-nonnull-attribute) tells
// codegen that something may live at address 0.

struct S { char c[4]; };
template <S s> constexpr const char *q () { return s.c; }
static_assert (q<S{"abc"}> () != nullptr);	// template parameter object

inline int iv;
static_assert (&iv != nullptr);			// inline variable

template <class T> int vt = 0;
static_assert (&vt<int> != nullptr);		// variable template

template <class T> struct C { static int m; };
template <class T> int C<T>::m = 0;
static_assert (&C<int>::m != nullptr);		// static member of a class template

inline void fi () {}
static_assert (&fi != nullptr);			// inline function

int g;
static_assert (&g != nullptr);			// ordinary definition

extern int e;
static_assert (&e != nullptr);			// declared, not defined here

constexpr bool
is_null (const void *p)
{
  return p == nullptr;
}
static_assert (!is_null (&iv));
static_assert (!is_null (q<S{"xyz"}> ()));
