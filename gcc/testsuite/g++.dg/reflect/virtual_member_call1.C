// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A virtual member call reflects as a non-virtual one does: `b.f (x)` has
// the operands {x}, and `b * x` is an operator expression with {b, x}.
// { dg-final { scan-assembler "_Z2tfILDmid" } }

#include <meta>

using namespace std::meta;

struct S { int v; };

struct B
{
  virtual constexpr int f (int x) const { return x; }
  virtual constexpr int operator* (int x) const { return x; }
  virtual constexpr S g (int x) const { return {x}; }
};

constexpr int vcall (const B &b, int x) { return b.f (x); }
constexpr int vop (const B &b, int x) { return b * x; }
constexpr int vpcall (const B *p, int x) { return p->f (x); }
constexpr int vpop (const B *p, int x) { return *p * x; }
constexpr S vgcall (const B &b, int x) { return b.g (x); }
constexpr const B &pick (const B &b) { return b; }
constexpr int vsaved (const B &b, int x) { return pick (b) * x; }

consteval info
peel (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

consteval info
ret (info fn)
{
  return peel (return_operand_of (statements_of (body_of (fn))[0]));
}

consteval info
operand (info fn, int i)
{
  return peel (operands_of (ret (fn))[i]);
}

consteval bool
is_deref (info e)
{
  return (is_operator_expression (e)
	  && expression_operator_of (e) == operators::op_star);
}

static_assert (is_function_call (ret (^^vcall)));
static_assert (!is_operator_expression (ret (^^vcall)));
static_assert (operands_of (ret (^^vcall)).size () == 1);
static_assert (is_id_expression (operand (^^vcall, 0)));
static_assert (declaration_of (callee_of (ret (^^vcall))) == ^^B::f);

static_assert (operands_of (ret (^^vpcall)).size () == 1);
static_assert (declaration_of (callee_of (ret (^^vpcall))) == ^^B::f);

static_assert (operands_of (ret (^^vgcall)).size () == 1);
static_assert (declaration_of (callee_of (ret (^^vgcall))) == ^^B::g);

static_assert (is_operator_expression (ret (^^vop)));
static_assert (expression_operator_of (ret (^^vop)) == operators::op_star);
static_assert (operands_of (ret (^^vop)).size () == 2);
static_assert (is_id_expression (operand (^^vop, 0)));
static_assert (is_id_expression (operand (^^vop, 1)));

static_assert (is_operator_expression (ret (^^vpop)));
static_assert (is_deref (operand (^^vpop, 0)));

// The object `pick (b)` is evaluated once, but it is still the call.
static_assert (is_operator_expression (ret (^^vsaved)));
static_assert (is_function_call (operand (^^vsaved, 0)));
static_assert (!is_deref (operand (^^vsaved, 0)));

// callee_of a virtual call mangles as an id-expression.
template <info R> int tf () { return 1; }
int (*use) () = &tf<callee_of (ret (^^vcall))>;
