// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A local initialized by a call that takes another local of a class with a
// non-trivial destructor by value still has an initializer.

#include <meta>
#include <string_view>
#include <type_traits>

using namespace std::meta;

void destroyed (double);

struct T { double v; };
struct D { double v; ~D () { destroyed (v); } };

static_assert (std::is_trivially_destructible_v<T>);
static_assert (!std::is_trivially_destructible_v<D>);

T make_t (double x) { return {x}; }
T pass_t (T x) { return x; }
D make_d (double x) { return {x}; }
D pass_d (D x) { return x; }

double t_copy (double x) { T a = make_t (x); T b = pass_t (a); return b.v; }
double d_copy (double x) { D a = make_d (x); D b = pass_d (a); return b.v; }

// Whether every declaration statement that declares `b` has an initializer.
consteval bool
b_has_initializer (info fn)
{
  bool found = false;
  for (info s : statements_of (body_of (fn)))
    {
      if (!is_declaration_statement (s)
	  || identifier_of (declared_variable_of (s)) != std::string_view ("b"))
	continue;
      found = true;
      try
	{
	  initializer_of (declared_variable_of (s));
	}
      catch (const std::meta::exception &)
	{
	  return false;
	}
    }
  return found;
}

static_assert (b_has_initializer (^^t_copy));
static_assert (b_has_initializer (^^d_copy));

// `b`'s initializer is the call to pass_d.
static_assert (is_function_call
	       (initializer_of
		(declared_variable_of (statements_of (body_of (^^d_copy))[1]))));
