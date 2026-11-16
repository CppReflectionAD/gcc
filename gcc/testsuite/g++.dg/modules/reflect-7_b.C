// cpp_reflection_ad#246
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-7_a.H";

static_assert (compound (^^add, operators::op_plus_equals));
static_assert (compound (^^tsub<double>, operators::op_minus_equals));
static_assert (compound (^^tsub<float>, operators::op_minus_equals));
