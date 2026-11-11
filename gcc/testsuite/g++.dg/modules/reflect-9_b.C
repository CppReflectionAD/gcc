// cpp_reflection_ad#250
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-9_a.H";

static_assert (if_first (^^if_constexpr));
static_assert (if_first (^^tif_constexpr<int>));
static_assert (if_first (^^tif_constexpr<long>));

int
main ()
{
  if (if_constexpr (1) != 2 || tif_constexpr (2) != 3 || tif_constexpr (3L) != 4)
    __builtin_abort ();
}
