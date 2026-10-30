// cpp_reflection_ad#239
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }
// { dg-module-cmi M }

export module M;
import "reflect-5_a.H";

export inline double m_multi (double x) MULTI
export inline double m_split (double x) SPLIT
export inline double m_ctor (double x) CTOR
export inline double m_stat (double x) STAT
export template <typename T> T m_tmulti (T x) { T a = x, b = a * a; return a + b; }

static_assert (shape (^^m_multi) == 222);
static_assert (shape (^^m_split) == 112);
static_assert (shape (^^m_ctor) == 112);
static_assert (shape (^^m_stat) == 112);
static_assert (shape (^^m_tmulti<double>) == 222);
