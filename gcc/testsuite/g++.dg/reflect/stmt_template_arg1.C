// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// A statement has no mangling, so its reflection can't be a template
// argument, whichever way it gets there; clang gives the same error.  Nor
// can a reflection of an expression that isn't an id-expression yet.  Both
// used to be an ICE in reflection_mangle_prefix (cpp_reflection_ad#225).

#include <meta>

using namespace std::meta;

void f (int a, int b) { int c = a + b; c = a; }

constexpr info s = statements_of (body_of (^^f))[0];
constexpr info e = initializer_of (declared_variable_of (s));
// An id-expression can be a template argument.
constexpr info id = expression_of (statements_of (body_of (^^f))[1]);
constexpr info a = operands_of (id)[1];

struct S { info r; };

template <info R> int use_stmt () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <info R> int use_expr () { return 0; }	// { dg-message "sorry, unimplemented: mangling a reflection of an expression that is not an id-expression" }
template <info R> int use_id () { return 0; }
template <auto A> int use_auto () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <info R> int use_const () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <S X> int use_s () { return 0; }	// { dg-error "a reflection of a statement cannot be used as a template argument" }
template <S X> int use_s_expr () { return 0; }	// { dg-message "sorry, unimplemented: mangling a reflection of an expression that is not an id-expression" }

int x1 = use_stmt<s> ();
int x2 = use_expr<e> ();
int x3 = use_id<a> ();
int x4 = use_auto<s> ();
int x5 = use_const<reflect_constant (s)> ();
int x6 = use_s<S{s}> ();		// { dg-error "a reflection of a statement cannot be used as a template argument" }
int x7 = use_s_expr<S{e}> ();	// { dg-message "sorry, unimplemented: mangling a reflection of an expression that is not an id-expression" }

// define_static_array makes each element a template argument, so a template
// for over statements_of can't use it.
consteval int
count ()
{
  int k = 0;
  template for (constexpr info r : define_static_array (statements_of (body_of (^^f))))
    ++k;
  return k;
}
int x8 = count ();

// { dg-error "a reflection of a statement cannot be used as a template argument" "" { target *-*-* } 0 }
