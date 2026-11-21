// cpp_reflection_ad#269
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-12_a.H";

static_assert (blocks (^^then_block, 3));
static_assert (blocks (^^tthen_block<int>, 3));
static_assert (blocks (^^tthen_block<long>, 3));

int
main ()
{
  if (then_block (1) != 2 || then_block (0) != 0 || tthen_block (2L) != 3)
    __builtin_abort ();
}
