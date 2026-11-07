// cpp_reflection_ad#245
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-8_a.H";

static_assert (block_first (^^empty_block));
static_assert (block_first (^^tempty_block<double>));
static_assert (block_first (^^tempty_block<float>));
