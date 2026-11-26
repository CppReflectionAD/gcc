// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fno-threadsafe-statics -Wno-unused-label" }
// As static_local_init3.C, with the guard that -fno-threadsafe-statics
// tests and sets directly (cpp_reflection_ad#298).

#include "static_local_init3.C"
