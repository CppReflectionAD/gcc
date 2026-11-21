// cpp_reflection_ad#270
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-11.h"

static_assert (if_parts (^^no_else, 2));
static_assert (if_parts (^^tno_else<int>, 2));
