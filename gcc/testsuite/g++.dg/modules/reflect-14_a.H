// cpp_reflection_ad#278
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-14.h"

static_assert (switch_with (^^cond_decl, 3));
static_assert (switch_with (^^destroyed, 3));
static_assert (switch_with (^^in_template<int>, 3));
