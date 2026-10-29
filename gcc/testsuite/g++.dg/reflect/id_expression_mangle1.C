// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection" }
// An id-expression compares unequal to a reflection of the entity it names,
// so as a template argument it gets a mangling of its own.

#include <meta>

using namespace std::meta;

int g = 1;
constexpr int one (int x) { return x; }
constexpr int callf (int x) { return one (x); }
constexpr int useg () { int b = g; return b; }
constexpr int usep (int p) { return p; }

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
  auto s = statements_of (body_of (fn));
  return peel (return_operand_of (s[s.size () - 1]));
}

template <info R> int f () { return R == ^^one ? 1 : 2; }

constexpr info callee = callee_of (ret (^^callf));
constexpr info g_use
  = peel (initializer_of (declared_variable_of (statements_of (body_of (^^useg))[0])));
constexpr info p_use = ret (^^usep);
constexpr info p_parm = parameters_of (^^usep)[0];

static_assert (callee != ^^one);
static_assert (g_use != ^^g);
static_assert (p_use != p_parm);

int
main ()
{
  if (f<^^one> () != 1 || f<callee> () != 2)
    __builtin_abort ();
  if (f<^^g> () != 2 || f<g_use> () != 2)
    __builtin_abort ();
  if (f<p_parm> () != 2 || f<p_use> () != 2)
    __builtin_abort ();
}
