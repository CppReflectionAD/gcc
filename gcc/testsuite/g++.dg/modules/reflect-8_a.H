// cpp_reflection_ad#245
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-8.h"

static_assert (block_first (^^empty_block));
static_assert (block_first (^^tempty_block<double>));
