// cpp_reflection_ad#298: the declaration of a constant-initialized static
// local with a non-trivial destructor reaches an importer of the body as one
// statement, without the `if' that registers the destructor.  The header
// doesn't include <meta>, so that the guard is the only entry of the
// reflection tables for its bodies.

struct D { constexpr D () {} ~D () {} int v = 1; };

inline int
with_static (int x)
{
  static D b;
  return b.v + x;
}
