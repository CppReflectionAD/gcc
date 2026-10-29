// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fno-threadsafe-statics" }
// As static_local_init1.C, with the guard that -fno-threadsafe-statics
// tests and sets directly (cpp_reflection_ad#230).

#include "static_local_init1.C"
