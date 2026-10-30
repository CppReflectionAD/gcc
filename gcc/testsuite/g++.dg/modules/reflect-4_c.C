// cpp_reflection_ad#235
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import M;
import "reflect-4_a.H";

static_assert (declarations_then_return (^^c_all, 11));
static_assert (declarations_then_return (^^i_all, 11));
static_assert (declarations_then_return (^^t_all<int>, 11));
static_assert (declarations_then_return (^^t_all<long>, 11));
static_assert (declarations_then_return (^^t_dep<N::E>, 1));
static_assert (c_all (1) == 3);
