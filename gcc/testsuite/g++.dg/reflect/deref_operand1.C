// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A dereference bound to a reference is the operand of the binding, although
// the front end cancels the `&*`.  A written unary plus stays one.

#include <meta>
#include <string_view>

using namespace std::meta;

struct S { double v; };
struct N { double v; N (double); N (const N &); ~N (); };
struct M { double v; double operator* (double) const; };

double ref_d (const double &);
double ref_s (const S &);
double ref_n (const N &);
double ref_p (const double *const &);
double val_d (double);
double val_s (S);
double val_n (N);
const double *getp ();

// Bound to a reference: (const double &) NON_LVALUE_EXPR <p>.
double arg_d (const double *p) { return ref_d (*p); }
double arg_s (const S *p) { return ref_s (*p); }
double arg_n (const N *p) { return ref_n (*p); }
// Copied into a by-value parameter, from a reference to the source.
double copy_s (const S *p) { return val_s (*p); }
double copy_n (const N *p) { return val_n (*p); }
// Not a reference at all, so never cancelled.
double scalar (const double *p) { return val_d (*p); }
// The pointer is a prvalue: (const double &) getp ().
double from_call () { return ref_d (*getp ()); }
// Adding const in the binding.
double adds_const (double *p) { return ref_d (*p); }
// The referent is itself a pointer.
double twice (const double *const *pp) { return ref_p (*pp); }
// Not an argument.
double &returned (double *p) { return *p; }
double
initialized (const double *p)
{
  const double &r = *p;
  return r;
}
// In a template.
template <typename T> double tmpl (const T *p) { return ref_d (*p); }
// The object of a member operator.
double object (const M *p, double x) { return *p * x; }

// Written unary plus, including bound to a reference through a temporary.
const double *plus_p (const double *p) { return +p; }
double plus_x (double x) { return +x; }
double plus_bound (const double *p) { return ref_p (+p); }
double plus_d (double x) { return ref_d (+x); }
// A name bound to a reference has no operator at all.
double name (double x) { return ref_d (x); }

// Prvalue pointers: (const double &) (p + 8) and (const S &) this.
double offset (const double *p) { return ref_d (*(p + 1)); }
struct T { double v; double self () const; };
double ref_t (const T &);
double T::self () const { return ref_t (*this); }

// Pointers under a conversion to a reference, none from a dereference:
// (const N &) (N *) a, (const S &) (c ? &a : &b) and
// (const N &) (c ? (N *) a : (N *) b).
double name_n (N a) { return ref_n (a); }
double cond_s (bool c, S a, S b) { return ref_s (c ? a : b); }
double cond_n (bool c, N a, N b) { return ref_n (c ? a : b); }
double cond_d (bool c, double a, double b) { return ref_d (c ? a : b); }
// x = y, (const double &) &x and ++x, (const double &) &x.
double assign (double x, double y) { return ref_d (x = y); }
double prefix (double x) { return ref_d (++x); }
// (const double &) l has a reference operand, not a pointer.
double reinterp (const long &l) { return ref_d (reinterpret_cast<const double &> (l)); }

consteval info
ret (info fn)
{
  return return_operand_of (statements_of (body_of (fn))[0]);
}

consteval info
strip (info e)
{
  while (is_conversion (e) && !operands_of (e).empty ())
    e = operands_of (e)[0];
  return e;
}

consteval info
argument (info fn)
{
  return strip (operands_of (ret (fn))[0]);
}

consteval bool
op_is (info e, operators o)
{
  return is_operator_expression (e) && expression_operator_of (e) == o;
}

// E is `*NAME`, with nothing between the `*` and the name.
consteval bool
derefs (info e, std::string_view source)
{
  if (!op_is (e, operators::op_star))
    return false;
  auto o = operands_of (e);
  return (o.size () == 1 && is_id_expression (strip (o[0]))
	  && identifier_of (declaration_of (strip (o[0]))) == source);
}

static_assert (derefs (argument (^^arg_d), "p"));
static_assert (derefs (argument (^^arg_s), "p"));
static_assert (derefs (argument (^^arg_n), "p"));
static_assert (derefs (argument (^^copy_s), "p"));
static_assert (derefs (argument (^^copy_n), "p"));
static_assert (derefs (argument (^^scalar), "p"));
static_assert (derefs (argument (^^adds_const), "p"));
static_assert (derefs (argument (^^twice), "pp"));
static_assert (derefs (strip (ret (^^returned)), "p"));
static_assert (derefs (argument (^^tmpl<double>), "p"));
constexpr info r_var = declared_variable_of (statements_of (body_of (^^initialized))[0]);
static_assert (derefs (strip (initializer_of (r_var)), "p"));

static_assert (op_is (argument (^^from_call), operators::op_star));
static_assert (is_function_call (strip (operands_of (argument (^^from_call))[0])));

static_assert (derefs (operands_of (ret (^^object))[0], "p"));

static_assert (op_is (strip (ret (^^plus_p)), operators::op_plus));
static_assert (op_is (strip (ret (^^plus_x)), operators::op_plus));
static_assert (op_is (argument (^^plus_bound), operators::op_plus));
static_assert (op_is (argument (^^plus_d), operators::op_plus));

static_assert (is_id_expression (argument (^^name)));

static_assert (op_is (argument (^^offset), operators::op_star));
static_assert (op_is (argument (^^T::self), operators::op_star));

static_assert (is_id_expression (argument (^^name_n)));
static_assert (is_conditional_operator (argument (^^cond_s)));
static_assert (is_conditional_operator (argument (^^cond_n)));
static_assert (is_conditional_operator (argument (^^cond_d)));
static_assert (!op_is (argument (^^assign), operators::op_star));
static_assert (!op_is (argument (^^prefix), operators::op_star));
static_assert (!op_is (argument (^^reinterp), operators::op_star));
