// cpp_reflection_ad#239
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodule-header -freflection" }
// { dg-module-cmi {} }

#include "reflect-5.h"

static_assert (shape (^^multi) == 222);
static_assert (shape (^^split) == 112);
static_assert (shape (^^ctor) == 112);
static_assert (shape (^^stat) == 112);
static_assert (shape (^^tmulti<double>) == 222);
