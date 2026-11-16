// cpp_reflection_ad#268
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-10_a.H";

static_assert (if_first (^^if_true));
static_assert (if_first (^^tif_sizeof<int>));
static_assert (if_first (^^tif_sizeof<long>));

int
main ()
{
  if (if_true (1) != 2 || tif_sizeof (2) != 3 || tif_sizeof (3L) != 4)
    __builtin_abort ();
}
