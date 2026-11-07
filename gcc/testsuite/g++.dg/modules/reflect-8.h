// cpp_reflection_ad#245: a block that declares nothing reaches an importer of
// the body as a compound statement.

#include <meta>

using namespace std::meta;

inline double empty_block (double x) { { } return x; }
template <typename T> T tempty_block (T x) { { } return x; }

consteval bool
block_first (info fn)
{
  auto s = statements_of (body_of (fn));
  return (s.size () == 2
	  && is_compound_statement (s[0])
	  && statements_of (s[0]).size () == 0
	  && is_return_statement (s[1]));
}
