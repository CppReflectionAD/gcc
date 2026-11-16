// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A glvalue of class type passed by value is the operand of a conversion that
// constructs the parameter, whether the class is copied trivially or not.

#include <meta>
#include <string_view>
#include <utility>

using namespace std::meta;

// Copied trivially: TARGET_EXPR <D.1, a>.
struct S { double v; };
// Passed by invisible reference: &TARGET_EXPR <D.1, N::N (&D.1, &a)>.
struct N { double v; N (const N &); ~N (); };

struct H { S s; N n; };
struct D : S { double w; };

S operator+ (S, S);
N operator+ (N, N);
struct M
{
  double operator* (S) const;
  double operator* (N) const;
  double f (S) const;
  double f (N) const;
};
double g (S);
double g (N);
template <typename T> double t (T);
struct C { C (S); C (N); };
S &rs ();
N &rn ();
S ms ();
N mn ();

S add_s (S x, S a) { return x + a; }
N add_n (N x, N a) { return x + a; }
double call_s (S a) { return g (a); }
double call_n (N a) { return g (a); }
double op_s (M m, S a) { return m * a; }
double op_n (M m, N a) { return m * a; }
double member_s (M m, S a) { return m.f (a); }
double member_n (M m, N a) { return m.f (a); }
double tmpl_s (S a) { return t (a); }
double tmpl_n (N a) { return t (a); }
double ref_s (const S &r) { return g (r); }
double ref_n (const N &r) { return g (r); }
double move_s (S &&r) { return g (std::move (r)); }
double field_s (H h) { return g (h.s); }
double field_n (H h) { return g (h.n); }
double deref_s (const S *p) { return g (*p); }
double deref_n (const N *p) { return g (*p); }
double slice (D d) { return g (d); }
double cond_s (bool c, S a, S b) { return g (c ? a : b); }
double cond_n (bool c, N a, N b) { return g (c ? a : b); }
double ref_call_s () { return g (rs ()); }
double ref_call_n () { return g (rn ()); }
double prvalue_s () { return g (ms ()); }
double prvalue_n () { return g (mn ()); }
double literal_s () { return g (S{1.0}); }
C ctor_s (S a) { return C (a); }
C ctor_n (N a) { return C (a); }

consteval info
ret (info fn)
{
  return return_operand_of (statements_of (body_of (fn))[0]);
}

// The last operand of FN's returned expression.
consteval info
last (info fn)
{
  info e = ret (fn);
  while (!is_function_call (e) && operands_of (e).size () == 1)
    e = operands_of (e)[0];
  auto o = operands_of (e);
  return o[o.size () - 1];
}

consteval info
strip (info e)
{
  while (is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

// The argument is a construct with one operand, so a conversion.
consteval bool
is_copy (info e)
{
  return (is_expression (e) && is_conversion (e) && is_construct (e)
	  && operands_of (e).size () == 1);
}

// Without its conversions, the argument names the source.
consteval bool
copies_name (info e, std::string_view source)
{
  return is_copy (e) && is_id_expression (strip (e))
	 && identifier_of (declaration_of (strip (e))) == source;
}

consteval bool
copies (info fn, std::string_view source)
{
  return copies_name (last (fn), source);
}

// A walk over the operands reaches a name.
consteval bool
reaches_name (info e, int depth = 0)
{
  if (is_id_expression (e))
    return true;
  if (depth == 8)
    return false;
  for (info o : operands_of (e))
    if (reaches_name (o, depth + 1))
      return true;
  return false;
}

static_assert (copies (^^add_s, "a"));
static_assert (copies (^^add_n, "a"));
static_assert (copies (^^call_s, "a"));
static_assert (copies (^^call_n, "a"));
static_assert (copies (^^op_s, "a"));
static_assert (copies (^^op_n, "a"));
static_assert (copies (^^member_s, "a"));
static_assert (copies (^^member_n, "a"));
static_assert (copies (^^tmpl_s, "a"));
static_assert (copies (^^tmpl_n, "a"));
static_assert (copies (^^ref_s, "r"));
static_assert (copies (^^ref_n, "r"));
static_assert (copies_name (operands_of (ret (^^ctor_s))[0], "a"));
static_assert (copies_name (operands_of (ret (^^ctor_n))[0], "a"));

// Both operands of the operator, not just the last.
static_assert (operands_of (ret (^^add_s)).size () == 2);
static_assert (is_copy (operands_of (ret (^^add_s))[0]));
static_assert (operands_of (ret (^^add_n)).size () == 2);
static_assert (is_copy (operands_of (ret (^^add_n))[0]));

// A source that isn't a name is still the copy's operand.
static_assert (is_copy (last (^^move_s)));
static_assert (is_copy (last (^^field_s)));
static_assert (is_copy (last (^^field_n)));
static_assert (is_copy (last (^^deref_s)));
static_assert (expression_operator_of (strip (last (^^deref_s))) == operators::op_star);
static_assert (is_copy (last (^^deref_n)));
static_assert (expression_operator_of (strip (last (^^deref_n))) == operators::op_star);
static_assert (is_copy (last (^^slice)));
static_assert (reaches_name (last (^^slice)));
static_assert (reaches_name (last (^^field_s)));
static_assert (reaches_name (last (^^field_n)));
static_assert (is_copy (last (^^cond_s)));
static_assert (is_conditional_operator (strip (last (^^cond_s))));
static_assert (is_copy (last (^^cond_n)));
static_assert (is_conditional_operator (strip (last (^^cond_n))));
static_assert (is_copy (last (^^ref_call_s)));
static_assert (is_function_call (strip (last (^^ref_call_s))));
static_assert (is_copy (last (^^ref_call_n)));
static_assert (is_function_call (strip (last (^^ref_call_n))));

// A prvalue isn't copied: the argument is the call.
static_assert (is_function_call (last (^^prvalue_s)));
static_assert (!is_conversion (last (^^prvalue_s)));
static_assert (is_function_call (last (^^prvalue_n)));
static_assert (!is_conversion (last (^^prvalue_n)));
static_assert (is_construct (last (^^literal_s)));
