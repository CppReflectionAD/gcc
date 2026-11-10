// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// Test std::meta::variable_of outside the function's body, an extension to
// P3096 that the clang fork shares.

#include <meta>

using namespace std::meta;

consteval int fn (int p) { return p; }

static_assert (is_variable (variable_of (parameters_of (^^fn)[0])));
static_assert (type_of (variable_of (parameters_of (^^fn)[0])) == ^^int);
static_assert (variable_of (parameters_of (^^fn)[0])
	       != parameters_of (^^fn)[0]);

// Parameters of different functions are different, even when they have the
// same type and position.
consteval int fn2 (int p) { return p; }
static_assert (variable_of (parameters_of (^^fn)[0])
	       != variable_of (parameters_of (^^fn2)[0]));
static_assert (parameters_of (^^fn)[0] != parameters_of (^^fn2)[0]);

// The result is the variable that a use of the parameter in the body names,
// even when the function was declared before its definition.
consteval info
first_use (info f)
{
  info e = return_operand_of (statements_of (body_of (f))[0]);
  while (!is_id_expression (e))
    e = operands_of (e)[0];
  return declaration_of (e);
}

int redeclared (int a, int b);
constexpr info early_param = parameters_of (^^redeclared)[0];
int redeclared (int a, int b) { return a * b; }
static_assert (variable_of (parameters_of (^^redeclared)[0])
	       == first_use (^^redeclared));
static_assert (variable_of (parameters_of (^^redeclared)[1])
	       != first_use (^^redeclared));
// Also for a reflection of a parameter taken before the definition.
static_assert (variable_of (early_param) == first_use (^^redeclared));

// Each element of an expanded pack has its own (unnamed) variable, including
// in a specialization nothing has instantiated yet.
// The return type is long so that no narrowing conversion lets the body be
// reassociated, which would change which element first_use finds.
template <typename... Ts> long pack (Ts... xs) { return (xs + ...); }
constexpr auto pack_params
  = std::define_static_array (parameters_of (^^pack<int, long, int>));
static_assert (pack_params.size () == 3);
static_assert (variable_of (pack_params[0]) != variable_of (pack_params[1]));
static_assert (variable_of (pack_params[0]) != variable_of (pack_params[2]));
static_assert (type_of (variable_of (pack_params[1])) == ^^long);
// The parameters themselves are told apart too.
static_assert (pack_params[0] != pack_params[2]);
static_assert (variable_of (pack_params[0]) == first_use (^^pack<int, long, int>));

// A specialization's parameter reflected before it is instantiated.
template <typename T> T tmpl (T t) { return t; }
constexpr info tmpl_param = parameters_of (^^tmpl<double>)[0];
static_assert (type_of (variable_of (tmpl_param)) == ^^double);
static_assert (variable_of (tmpl_param) == first_use (^^tmpl<double>));
static_assert (variable_of (parameters_of (^^tmpl<double>)[0])
	       == first_use (^^tmpl<double>));

// Member functions: the object parameter isn't in parameters_of.
struct S
{
  int mem (int x) const { return x; }
  static int smem (int y) { return y; }
};
static_assert (variable_of (parameters_of (^^S::mem)[0]) == first_use (^^S::mem));
static_assert (variable_of (parameters_of (^^S::smem)[0])
	       == first_use (^^S::smem));
