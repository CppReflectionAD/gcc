// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }
// constant_of of an id-expression answers as constant_of of the entity it
// names, as on clang: an id-expression naming a constant gives that constant.

#include <meta>

using namespace std::meta;

struct P { double a; };
inline constexpr double k = 2.5;
inline constexpr P kp{1.5};
inline const int ci = 7;
inline double mut = 1.0;

const double &f_k () { return k; }
const P &f_kp () { return kp; }
const int &f_ci () { return ci; }
double &f_mut () { return mut; }
double &f_param (double &x) { return x; }

consteval info
peel (info e)
{
  while (is_expression (e) && is_conversion (e))
    e = operands_of (e)[0];
  return e;
}

consteval info
ret (info fn)
{
  return peel (return_operand_of (statements_of (body_of (fn))[0]));
}

consteval bool
throws_constant_of (info r)
{
  try { constant_of (r); }
  catch (const exception &) { return true; }
  return false;
}

static_assert (is_id_expression (ret (^^f_k)));
static_assert (constant_of (ret (^^f_k)) == constant_of (^^k));
static_assert ([: constant_of (ret (^^f_k)) :] == 2.5);

static_assert (is_id_expression (ret (^^f_kp)));
static_assert (constant_of (ret (^^f_kp)) == constant_of (^^kp));
static_assert ([: constant_of (ret (^^f_kp)) :].a == 1.5);

static_assert (is_id_expression (ret (^^f_ci)));
static_assert (constant_of (ret (^^f_ci)) == constant_of (^^ci));
static_assert ([: constant_of (ret (^^f_ci)) :] == 7);

// Not constants, with the same answer as for the entity.
static_assert (is_id_expression (ret (^^f_mut)));
constexpr info c_mut = constant_of (ret (^^f_mut)); // { dg-error "not usable in a constant expression" }
constexpr info c_mut_entity = constant_of (^^mut); // { dg-error "not usable in a constant expression" }

static_assert (is_id_expression (ret (^^f_param)));
static_assert (throws_constant_of (ret (^^f_param)));
static_assert (throws_constant_of (parameters_of (^^f_param)[0]));

// The id-expression is still not the entity.
static_assert (ret (^^f_k) != ^^k);
static_assert (!is_variable (ret (^^f_k)));
static_assert (declaration_of (ret (^^f_k)) == ^^k);
