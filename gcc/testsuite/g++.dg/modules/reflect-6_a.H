// cpp_reflection_ad#237
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-6.h"

static_assert (null_first (^^null_stmt));
static_assert (null_first (^^tnull_stmt<double>));
