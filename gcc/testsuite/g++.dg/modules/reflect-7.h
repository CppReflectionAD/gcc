// cpp_reflection_ad#246: a compound assignment's operator reaches an
// importer of the body.

#include <meta>

using namespace std::meta;

inline void add (double &a, double b) { a += b; }
template <typename T> void tsub (T &a, T b) { a -= b; }

consteval bool
compound (info fn, operators op)
{
  info e = expression_of (statements_of (body_of (fn))[0]);
  return (expression_operator_of (e) == op
	  && operands_of (e).size () == 2);
}
