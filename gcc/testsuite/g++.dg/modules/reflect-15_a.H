// cpp_reflection_ad#287
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection -Wno-switch-unreachable" }
// { dg-module-cmi {} }

#include "reflect-15.h"

static_assert (labeled_shape (^^labeled));
