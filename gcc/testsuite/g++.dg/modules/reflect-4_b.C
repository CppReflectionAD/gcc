// cpp_reflection_ad#235
// { dg-do compile { target c++26 } }
// { dg-additional-options "-fmodules -freflection" }
// { dg-module-cmi M }

// Each block declaration that declares no variable is still a declaration
// statement once the function that has it is imported.

export module M;
import "reflect-4_a.H";

export namespace N
{
  constexpr int g (int x) { return x; }
  enum class E { a, b };
}

#define BODY							\
  using T = int; typedef int U; struct L { int v; };		\
  enum F { fa, fb }; struct Fw; static_assert (true);		\
  consteval { } namespace M = N; using N::g;			\
  using namespace N; using enum N::E;

export constexpr int c_all (int x) { BODY return x + int (b) + fb; }
export inline int i_all (int x) { BODY return x + int (b) + fb; }
export template <typename X> X t_all (X x) { BODY return x + int (b) + fb; }
export template <typename E> int t_dep (int x) { using E::b; return x + int (b); }

// Whether FN's body is DECLS declaration statements that aren't simple
// declarations, then a return.
export consteval bool
declarations_then_return (std::meta::info fn, std::size_t decls)
{
  auto stmts = std::meta::statements_of (std::meta::body_of (fn));
  if (stmts.size () != decls + 1
      || !std::meta::is_return_statement (stmts[decls]))
    return false;
  for (std::size_t i = 0; i < decls; ++i)
    if (!std::meta::is_declaration_statement (stmts[i])
	|| std::meta::is_simple_declaration (stmts[i])
	|| !std::meta::declarators_of (stmts[i]).empty ())
      return false;
  return true;
}

static_assert (declarations_then_return (^^c_all, 11));
static_assert (declarations_then_return (^^i_all, 11));
static_assert (declarations_then_return (^^t_all<int>, 11));
static_assert (declarations_then_return (^^t_dep<N::E>, 1));
