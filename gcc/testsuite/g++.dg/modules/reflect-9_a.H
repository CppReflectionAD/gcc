// cpp_reflection_ad#250
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-9.h"

static_assert (if_first (^^if_constexpr));
static_assert (if_first (^^tif_constexpr<int>));
