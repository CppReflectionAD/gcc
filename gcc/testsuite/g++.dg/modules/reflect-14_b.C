// cpp_reflection_ad#278
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-14_a.H";

static_assert (switch_with (^^cond_decl, 3));
static_assert (switch_with (^^destroyed, 3));
static_assert (switch_with (^^in_template<int>, 3));
static_assert (switch_with (^^in_template<long>, 3));

int
main ()
{
  if (cond_decl (1) != 2 || cond_decl (0) != 3
      || destroyed (1) != 2 || destroyed (0) != 4
      || in_template (2) != 3 || in_template (0L) != 5)
    __builtin_abort ();
}
