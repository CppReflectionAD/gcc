// { dg-do link { target c++26 } }
// { dg-additional-options "-freflection" }
// An operator kept as written for reflection is still folded for the code,
// even at -O0.

extern void link_error ();

int
main ()
{
  if (! __builtin_constant_p (&"Hello"[0]))
    link_error ();
  if (!(1 + 1 == 2))
    link_error ();
}
