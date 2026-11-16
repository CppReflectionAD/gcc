// { dg-do compile { target c++20 } }
// { dg-require-weak "" }
// { dg-options "-fno-delete-null-pointer-checks" }
// A weak declaration may still be null, so comparing its address with null
// isn't a constant expression, with or without the flag.  A weak definition
// is defined here, as it is without the flag.

extern int w __attribute__ ((weak));
static_assert (&w != nullptr);	// { dg-error "non-constant condition" }
// { dg-error "is not a constant expression" "" { target *-*-* } .-1 }

int wd __attribute__ ((weak)) = 0;
static_assert (&wd != nullptr);

inline int iv;
static_assert (&iv != nullptr);
