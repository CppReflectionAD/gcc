// { dg-do run { target c++26 } }
// { dg-options "-freflection --param ggc-min-expand=0 --param ggc-min-heapsize=0" }
// A typedef of a variably modified type is a declaration statement that
// isn't a simple declaration (cpp_reflection_ad#235), and its bounds are
// still evaluated once.  A bound with side effects is first stored in a
// temporary, which statements_of still gives as statements of its own.

#include <meta>

using namespace std::meta;

int f_vla (int n) { typedef int V[n + 1]; return sizeof (V) / sizeof (int); }
template <typename T> int t_vla (int n) { typedef T V[n + 2]; return sizeof (V) / sizeof (T); }
template int t_vla<int> (int);

int g;
int next () { return ++g; }

int f_vla_call (int n) { typedef int V[n + next ()]; return sizeof (V) / sizeof (int); }
template <typename T> int t_vla_call (int n) { typedef T V[n + next ()]; return sizeof (V) / sizeof (T); }

// Whether FN's body is a declaration statement with no declarators, then a
// return.
consteval bool
declaration_then_return (info fn)
{
  auto stmts = statements_of (body_of (fn));
  return (stmts.size () == 2
	  && is_declaration_statement (stmts[0])
	  && !is_expression_statement (stmts[0])
	  && !is_simple_declaration (stmts[0])
	  && declarators_of (stmts[0]).empty ()
	  && is_return_statement (stmts[1]));
}

static_assert (declaration_then_return (^^f_vla));
static_assert (declaration_then_return (^^t_vla<int>));

// In a constructor, whose body is cloned (as in g++.dg/ext/vla18.C).
int v[1][10];
struct A
{
  int r;
  A (int i)
  {
    typedef int T[1][i];
    T *x = (T *) v;
    (*x)[0][0] = 0;
    r = sizeof (T) / sizeof (int);
  }
};

int
main ()
{
  if (f_vla (1) != 2 || t_vla<int> (1) != 3)
    __builtin_abort ();
  if (f_vla_call (1) != 2 || t_vla_call<int> (1) != 3 || g != 2)
    __builtin_abort ();
  A a (10);
  if (a.r != 10)
    __builtin_abort ();
}
