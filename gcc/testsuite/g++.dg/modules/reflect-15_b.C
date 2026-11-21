// cpp_reflection_ad#287
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection -Wno-switch-unreachable" }

import "reflect-15_a.H";

static_assert (labeled_shape (^^labeled));

int
main ()
{
  if (labeled (3) != 2 || labeled (0) != 0)
    __builtin_abort ();
}
