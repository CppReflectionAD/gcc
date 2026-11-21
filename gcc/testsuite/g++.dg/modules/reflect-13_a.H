// cpp_reflection_ad#278
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-13.h"

static_assert (if_with (^^cond_decl, 4));
static_assert (if_with (^^destroyed, 4));
static_assert (if_with (^^in_template<int>, 4));
