// cpp_reflection_ad#237: a null statement's marker reaches an importer of the
// body.

#include <meta>

using namespace std::meta;

inline double null_stmt (double x) { ; return x; }
template <typename T> T tnull_stmt (T x) { ; return x; }

consteval bool
null_first (info fn)
{
  auto s = statements_of (body_of (fn));
  return (s.size () == 2
	  && is_expression_statement (s[0])
	  && !is_declaration_statement (s[0])
	  && is_return_statement (s[1]));
}
