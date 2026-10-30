// cpp_reflection_ad#239
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

// The definitions here come first, so the imported ones are duplicates.

#include "reflect-5.h"
import "reflect-5_a.H";

static_assert (shape (^^multi) == 222);
static_assert (shape (^^split) == 112);
static_assert (shape (^^ctor) == 112);
static_assert (shape (^^stat) == 112);
static_assert (shape (^^tmulti<double>) == 222);
static_assert (shape (^^tmulti<float>) == 222);
