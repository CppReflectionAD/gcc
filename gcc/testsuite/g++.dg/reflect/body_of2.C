// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// body_of instantiates a function template specialization in the middle of
// a constant evaluation, which must not collect garbage.

#include <meta>

using namespace std::meta;

template <typename U> U explicit_inst (U x) { return x; }
template double explicit_inst<double> (double);

template <typename U> U implicit_inst (U x) { return x; }
double use (double x) { return implicit_inst (x); }

template <typename U> U never_used (U x) { return x; }

consteval bool
one_statement (info fn)
{
  return statements_of (body_of (fn)).size () == 1;
}

static_assert (statements_of (body_of (^^explicit_inst<double>)).size () == 1);
static_assert (one_statement (^^implicit_inst<double>));
static_assert (one_statement (^^never_used<int>));
