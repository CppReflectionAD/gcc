// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Reflections that compare equal are the same template argument.  Their
// hashes used to differ, which made two specializations of one template
// ("canonical types differ for identical types").

#include <meta>
#include <type_traits>

using namespace std::meta;

template <info I> struct X {};

// template_of gives the TEMPLATE_DECL; ^^f gives an OVERLOAD holding it.
template <int N> int f () { return N; }
template <int N> int g () { return N; }

static_assert (template_of (^^f<3>) == ^^f);
static_assert (std::is_same_v<X<template_of (^^f<3>)>, X<^^f>>);
static_assert (!std::is_same_v<X<^^f>, X<^^g>>);

template <info K> struct reg;
template <> struct reg<^^f> {};
static_assert (is_complete_type (substitute (^^reg, {reflect_constant (template_of (^^f<3>))})));
static_assert (!is_complete_type (substitute (^^reg, {reflect_constant (template_of (^^g<3>))})));

// The same for a member function template.
struct S { template <class T> void m (T); template <class T> void n (T); };
static_assert (std::is_same_v<X<template_of (^^S::m<int>)>, X<^^S::m>>);
static_assert (!std::is_same_v<X<^^S::m>, X<^^S::n>>);

// A parameter reflected before the definition is the same parameter as one
// reflected after it, though the definition adds a top-level const.
void h (int, long);
constexpr info early0 = parameters_of (^^h)[0];
constexpr info early1 = parameters_of (^^h)[1];
void h (const int a, const long b) {}
constexpr info late0 = parameters_of (^^h)[0];

static_assert (early0 == late0);
static_assert (std::is_same_v<X<early0>, X<late0>>);
static_assert (!std::is_same_v<X<early0>, X<early1>>);

// A parameter variable reflected inside the body.
int k (int p, int q)
{
  constexpr info rp = ^^p;
  static_assert (std::is_same_v<X<rp>, X<variable_of (parameters_of (^^k)[0])>>);
  static_assert (!std::is_same_v<X<rp>, X<^^q>>);
  return p + q;
}
