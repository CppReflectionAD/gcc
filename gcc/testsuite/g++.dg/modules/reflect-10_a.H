// cpp_reflection_ad#268
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-10.h"

static_assert (if_first (^^if_true));
static_assert (if_first (^^tif_sizeof<int>));
