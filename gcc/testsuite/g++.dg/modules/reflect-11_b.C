// cpp_reflection_ad#270
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-11_a.H";

static_assert (if_parts (^^no_else, 2));
static_assert (if_parts (^^tno_else<int>, 2));
static_assert (if_parts (^^tno_else<long>, 2));

int
main ()
{
  if (no_else (1) != 2 || no_else (0) != 0 || tno_else (2L) != 3)
    __builtin_abort ();
}
