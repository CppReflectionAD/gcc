// cpp_reflection_ad#239: what reflect.cc keeps in tables about a body's
// variables reaches an importer of the body.

#include <meta>

struct P { double a, b; };
struct C { double v; C (double d) : v (d) { } };

// A declaration with two declarators, an aggregate whose initializer isn't
// constant, a constructor call, and a static local with a dynamic
// initializer, each followed by a return.
#define MULTI { double a = x, b = a * a; return a + b; }
#define SPLIT { P p = { x, 1.0 }; return p.a; }
#define CTOR { C c (x); return c.v; }
#define STAT { static double s = x; return s; }

inline double multi (double x) MULTI
inline double split (double x) SPLIT
inline double ctor (double x) CTOR
inline double stat (double x) STAT
template <typename T> T tmulti (T x) { T a = x, b = a * a; return a + b; }

// 100 times the number of declarators of FN's first statement, a
// declaration, plus 10 times the number of them with an initializer, plus
// the number of statements, of which the last is a return.
consteval int
shape (std::meta::info fn)
{
  auto st = std::meta::statements_of (std::meta::body_of (fn));
  if (!std::meta::is_declaration_statement (st[0])
      || !std::meta::is_return_statement (st.back ()))
    return -1;
  int inits = 0;
  for (auto i : std::meta::initializers_of (st[0]))
    inits += i != std::meta::info {};
  return (int (std::meta::declarators_of (st[0]).size ()) * 100
	  + inits * 10 + int (st.size ()));
}
