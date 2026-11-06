// cpp_reflection_ad#237
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-6_a.H";

static_assert (null_first (^^null_stmt));
static_assert (null_first (^^tnull_stmt<double>));
static_assert (null_first (^^tnull_stmt<float>));
