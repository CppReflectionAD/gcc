// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A statement has no mangling, so a specialization whose argument is the
// reflection of a null statement, an alias declaration or a block can't be
// emitted, as with any other statement (stmt_template_arg1.C) and as with
// clang.  The first two were an ICE (cpp_reflection_ad#284); a block was
// mangled as if it were dependent (cpp_reflection_ad#285).

#include <meta>

using namespace std::meta;

int sink (int);

void
f (int x)
{
  ;
  using T = int;
  {
    sink (x);
  }
}

consteval info
st (int k)
{
  return statements_of (body_of (^^f))[k];
}

template <info R> int use_null () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <info R> int use_alias () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <info R> int use_block () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }

int x1 = use_null<st (0)> ();
int x2 = use_alias<st (1)> ();
int x3 = use_block<st (2)> ();
