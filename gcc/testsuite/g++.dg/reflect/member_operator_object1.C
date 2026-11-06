// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// The object operand of a member operator call is the expression in the
// source: `*this` and `*p` are dereferences, not the pointer, while a
// by-value or reference object is an id-expression.

#include <meta>

using namespace std::meta;

struct C
{
  int v;
  constexpr int operator* (int x) const { return v * x; }
  constexpr int self (int x) const { return *this * x; }
};
constexpr int via_ptr (const C *p, int x) { return *p * x; }
constexpr int via_ptr_paren (const C *p, int x) { return (*p) * x; }
constexpr int by_val (C c, int x) { return c * x; }
constexpr int by_ref (const C &r, int x) { return r * x; }

consteval info
peel (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

// Operand 0 of the operator call that FN returns.
consteval info
object (info fn)
{
  info e = peel (return_operand_of (statements_of (body_of (fn))[0]));
  if (!is_operator_expression (e) || operands_of (e).size () != 2)
    throw "not a binary operator call";
  return peel (operands_of (e)[0]);
}

consteval bool
is_deref (info e)
{
  return (is_operator_expression (e)
	  && expression_operator_of (e) == operators::op_star
	  && operands_of (e).size () == 1);
}

static_assert (is_deref (object (^^C::self)));
// `this` is a keyword, not an id-expression.
static_assert (!is_id_expression (peel (operands_of (object (^^C::self))[0])));

static_assert (is_deref (object (^^via_ptr)));
static_assert (is_deref (object (^^via_ptr_paren)));
static_assert (is_id_expression (peel (operands_of (object (^^via_ptr))[0])));
static_assert (identifier_of (declaration_of
				(peel (operands_of (object (^^via_ptr))[0])))
	       == "p");

static_assert (is_id_expression (object (^^by_val)));
static_assert (is_id_expression (object (^^by_ref)));
static_assert (!is_deref (object (^^by_ref)));
