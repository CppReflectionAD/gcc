// cpp_reflection_ad#298
// { dg-do run { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }

import "reflect-16_a.H";

#include <meta>

using namespace std::meta;

// with_static's body is b's declaration and a return.
consteval bool
one_declaration (info fn)
{
  auto s = statements_of (body_of (fn));
  return (s.size () == 2 && is_declaration_statement (s[0])
	  && identifier_of (declared_variable_of (s[0])) == "b"
	  && is_return_statement (s[1]));
}

static_assert (one_declaration (^^with_static));

int
main ()
{
  if (with_static (1) != 2)
    __builtin_abort ();
}
