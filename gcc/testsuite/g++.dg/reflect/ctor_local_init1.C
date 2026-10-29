// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A local of class type that a constructor initializes is one declaration
// statement, and its initializer is the construction, although
// expand_default_init calls the constructor in a statement after the
// declaration (cpp_reflection_ad#215).  So is a named return value, whose
// declaration finalize_nrv replaces with that call.

#include <meta>
#include <new>

using namespace std::meta;

struct C { constexpr C (double x) : v (x) {} double v; };
struct C0 { C0 (); double v; };
struct D { D (double x) : v (x) {} ~D (); double v; };
struct D0 { D0 (); ~D0 (); double v; };
struct E { constexpr E (double x, double y) : v (x), w (y) {} double v, w; };

double c_copy (double x) { C b = x; return b.v; }
double c_paren (double x) { C b (x); return b.v; }
double c_brace (double x) { C b{x}; return b.v; }
double c_const (double) { C b (1.0); return b.v; }
double c_copy_ctor (double x) { C a = x; C b (a); return b.v; }
double c0_default (double) { C0 b; return b.v; }
double c0_brace (double) { C0 b{}; return b.v; }
double d_paren (double x) { D b (x); return b.v; }
double e_paren (double x, double y) { E b (x, y); return b.v; }
double e_brace (double x, double y) { E b{x, y}; return b.w; }
// A named return value.  For D, returned by invisible reference,
// finalize_nrv replaces b's declaration with the constructor call on the
// return slot.
C nrv_paren (double x) { C b (x); return b; }
D nrv_d_paren (double x) { D b (x); return b; }
D nrv_d_brace (double x) { D b{x}; return b; }
D nrv_d_copy (double x) { D b = x; return b; }
D0 nrv_d0_default () { D0 b; return b; }
template <typename U> U tmpl (U x) { C b (x); return b.v; }
template double tmpl<double> (double);
constexpr double cx (double x) { C b (x); return b.v; }

double
in_block (double x)
{
  double s = 0;
  {
    E b (x, x);
    s = b.v;
  }
  return s;
}

// Placement new isn't the initialization of b.
double
placement (double x)
{
  C b (1.0);
  new (&b) C (x);
  return b.v;
}

// Whether BLOCK is b's declaration, with an initializer that constructs b
// from N arguments, and then a statement that isn't a declaration.
consteval bool
one_constructed_declaration (info block, std::size_t n)
{
  auto stmts = statements_of (block);
  if (stmts.size () != 2 || !is_declaration_statement (stmts[0])
      || is_expression_statement (stmts[0])
      || identifier_of (declared_variable_of (stmts[0])) != "b"
      || is_declaration_statement (stmts[1]))
    return false;
  auto inits = initializers_of (stmts[0]);
  if (inits.size () != 1 || inits[0] == info{})
    return false;
  info init = initializer_of (declared_variable_of (stmts[0]));
  return (init == inits[0] && !is_function_call (init)
	  && operands_of (init).size () == n);
}

consteval bool
body_is_one_constructed_declaration (info fn, std::size_t n)
{
  return one_constructed_declaration (body_of (fn), n);
}

static_assert (body_is_one_constructed_declaration (^^c_copy, 1));
static_assert (body_is_one_constructed_declaration (^^c_paren, 1));
static_assert (body_is_one_constructed_declaration (^^c_brace, 1));
static_assert (body_is_one_constructed_declaration (^^c0_default, 0));
static_assert (body_is_one_constructed_declaration (^^c0_brace, 0));
static_assert (body_is_one_constructed_declaration (^^d_paren, 1));
static_assert (body_is_one_constructed_declaration (^^e_paren, 2));
static_assert (body_is_one_constructed_declaration (^^e_brace, 2));
static_assert (body_is_one_constructed_declaration (^^nrv_paren, 1));
static_assert (body_is_one_constructed_declaration (^^nrv_d_paren, 1));
static_assert (body_is_one_constructed_declaration (^^nrv_d_brace, 1));
static_assert (body_is_one_constructed_declaration (^^nrv_d_copy, 1));
static_assert (body_is_one_constructed_declaration (^^nrv_d0_default, 0));
static_assert (body_is_one_constructed_declaration (^^tmpl<double>, 1));
static_assert (body_is_one_constructed_declaration (^^cx, 1));

// The constructor of a constant initialization is folded away.
static_assert (statements_of (body_of (^^c_const)).size () == 2);
static_assert (is_declaration_statement
	       (statements_of (body_of (^^c_const))[0]));
static_assert (initializers_of (statements_of (body_of (^^c_const))[0])[0]
	       != info{});

// A copy constructor too.
static_assert (statements_of (body_of (^^c_copy_ctor)).size () == 3);
static_assert (initializers_of (statements_of (body_of (^^c_copy_ctor))[1])[0]
	       != info{});

// The inner block of in_block.
static_assert (statements_of (body_of (^^in_block)).size () == 3);
static_assert (one_constructed_declaration
	       (statements_of (body_of (^^in_block))[1], 2));

// b's declaration, the placement new and the return.
static_assert (statements_of (body_of (^^placement)).size () == 3);
static_assert (is_expression_statement
	       (statements_of (body_of (^^placement))[1]));
