// cpp_reflection_ad#239
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

// An importer sees the same statements as the unit that defines them, from
// a header unit and from a named module.

import M;
import "reflect-5_a.H";

static_assert (shape (^^multi) == 222);
static_assert (shape (^^split) == 112);
static_assert (shape (^^ctor) == 112);
static_assert (shape (^^stat) == 112);
static_assert (shape (^^tmulti<double>) == 222);
static_assert (shape (^^tmulti<float>) == 222);

static_assert (shape (^^m_multi) == 222);
static_assert (shape (^^m_split) == 112);
static_assert (shape (^^m_ctor) == 112);
static_assert (shape (^^m_stat) == 112);
static_assert (shape (^^m_tmulti<double>) == 222);
static_assert (shape (^^m_tmulti<float>) == 222);
