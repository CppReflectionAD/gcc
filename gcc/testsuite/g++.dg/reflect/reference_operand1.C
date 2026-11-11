// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// cpp_reflection_ad#249: an operand that names a reference is an
// id-expression, as one that names a variable of another type is.  The
// dereference that convert_from_reference adds isn't in the source.

#include <meta>
#include <string_view>

using namespace std::meta;

void inc_value (int i) { ++i; }
void inc_ref (int &i) { ++i; }
void inc_local (int a) { int &r = a; ++r; }
void assign_ref (int &r, int x) { r = x; }
void add_assign_ref (int &r, int x) { r += x; }
int add_ref (int &r, int x) { return r + x; }
int read_ref (int &r) { return r; }
int read_rvalue_ref (int &&r) { return r; }
int &return_ref (int &r) { return r; }
int init_from_ref (int &r) { int y = r; return y; }

consteval info
expr (info fn, unsigned i)
{
  info s = statements_of (body_of (fn))[i];
  if (is_return_statement (s))
    return return_operand_of (s);
  if (is_declaration_statement (s))
    return initializers_of (s)[0];
  return expression_of (s);
}

consteval info
operand (info fn, unsigned i, unsigned k)
{
  return operands_of (expr (fn, i))[k];
}

consteval bool
names (info e, std::string_view name)
{
  return (is_id_expression (e)
	  && !is_conversion (e)
	  && operands_of (e).size () == 0
	  && identifier_of (declaration_of (e)) == name);
}

static_assert (names (operand (^^inc_value, 0, 0), "i"));
static_assert (names (operand (^^inc_ref, 0, 0), "i"));
static_assert (names (operand (^^inc_local, 1, 0), "r"));
static_assert (names (operand (^^assign_ref, 0, 0), "r"));
static_assert (names (operand (^^assign_ref, 0, 1), "x"));
static_assert (names (operand (^^add_assign_ref, 0, 0), "r"));
static_assert (names (operand (^^add_ref, 0, 0), "r"));
static_assert (names (expr (^^read_ref, 0), "r"));
static_assert (names (expr (^^read_rvalue_ref, 0), "r"));
static_assert (names (expr (^^return_ref, 0), "r"));
static_assert (names (expr (^^init_from_ref, 0), "r"));
