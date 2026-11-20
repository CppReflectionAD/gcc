// cpp_reflection_ad#278
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-13_a.H";

static_assert (if_with (^^cond_decl, 4));
static_assert (if_with (^^destroyed, 4));
static_assert (if_with (^^in_template<int>, 4));
static_assert (if_with (^^in_template<long>, 4));

int
main ()
{
  if (cond_decl (1) != 2 || cond_decl (-1) != 2
      || destroyed (1) != 2 || destroyed (0) != 3
      || in_template (2) != 3 || in_template (0L) != 4)
    __builtin_abort ();
}
