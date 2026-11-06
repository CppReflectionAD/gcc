// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// An id-expression, such as the callee of a call or a variable used as an
// operand, is an expression and not the entity it names, as on clang:
// entity queries answer false or throw, and declaration_of gives the entity.

#include <meta>

using namespace std::meta;

int g = 1;
constexpr double one (double x) { return x; }
constexpr double callf (double x) { return one (x); }
constexpr int useg () { return g; }

consteval info
ret (info fn)
{
  return return_operand_of (statements_of (body_of (fn))[0]);
}

consteval info
peel (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

consteval bool
throws_identifier_of (info r)
{
  try { (void) identifier_of (r); return false; }
  catch (const std::meta::exception &) { return true; }
}

consteval bool
throws_parent_of (info r)
{
  try { (void) parent_of (r); return false; }
  catch (const std::meta::exception &) { return true; }
}

constexpr info call = peel (ret (^^callf));
constexpr info callee = callee_of (call);
static_assert (is_id_expression (callee));
static_assert (is_expression (callee));
static_assert (operands_of (callee).empty ());
static_assert (!is_function (callee));
static_assert (!has_identifier (callee));
static_assert (!has_linkage (callee));
static_assert (throws_identifier_of (callee));
static_assert (throws_parent_of (callee));
static_assert (declaration_of (callee) == ^^one);
static_assert (callee != ^^one);
static_assert (!is_id_expression (^^one));

constexpr info use = peel (ret (^^useg));
static_assert (is_id_expression (use));
static_assert (!is_variable (use));
static_assert (!has_identifier (use));
static_assert (throws_identifier_of (use));
static_assert (declaration_of (use) == ^^g);
static_assert (use != ^^g);

// A walker that explores every expression's operands reaches the callee and
// stops there.
consteval int
count_id_expressions (info e)
{
  int n = is_id_expression (e);
  if (is_function_call (e))
    n += count_id_expressions (callee_of (e));
  if (is_expression (e))
    for (info op : operands_of (e))
      n += count_id_expressions (op);
  return n;
}

static_assert (count_id_expressions (call) == 2);	// one, x
