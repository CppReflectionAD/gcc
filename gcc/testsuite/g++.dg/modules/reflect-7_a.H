// cpp_reflection_ad#246
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-7.h"

static_assert (compound (^^add, operators::op_plus_equals));
static_assert (compound (^^tsub<double>, operators::op_minus_equals));
