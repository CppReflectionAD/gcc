// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// std::meta::variable_of works outside the function's body (an extension to
// P3096), but what it returns is still a local of that function: splicing it
// elsewhere is ill-formed, as for any other function's local.

#include <meta>

int fn (int p) { return p; }

int
read_outside ()
{
  return [: std::meta::variable_of (std::meta::parameters_of (^^fn)[0]) :]; // { dg-error "" }
}

// A function with no definition has no parameter variables.
int declared_only (int q);
constexpr auto bad
  = std::meta::variable_of (std::meta::parameters_of (^^declared_only)[0]); // { dg-error "uncaught exception" }
