// cpp_reflection_ad#269
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-12.h"

static_assert (blocks (^^then_block, 3));
static_assert (blocks (^^tthen_block<int>, 3));
