// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection -Wreturn-type -Wimplicit-fallthrough -Wduplicated-branches" }
// cpp_reflection_ad#250: an `if constexpr` kept for std::meta::statements_of
// runs, and warns, as the statement its condition selects.

#include <type_traits>

[[gnu::noipa]] int id (int x) { return x; }

template <typename T> int
then_only (T x)
{
  if constexpr (std::is_integral_v<T>)
    return x + 1;
}				// { dg-bogus "control reaches end" }

template <typename T> int
else_only (T x)
{
  if constexpr (!std::is_integral_v<T>)
    return 0;
  else
    return x + 2;
}				// { dg-bogus "control reaches end" }

int
not_a_template (int x)
{
  if constexpr (sizeof (int) == 1)
    return id (-1);
  else if constexpr (sizeof (int) >= 2)
    return x + 3;
  else
    return id (-2);
}				// { dg-bogus "control reaches end" }

template <typename T> int
not_taken (T x)
{
  if constexpr (!std::is_integral_v<T>)
    return id (-3);
  return x + 4;
}

template <typename T> int
same_branches (T x)
{
  if constexpr (sizeof (T) >= 2)	// { dg-bogus "condition has identical branches" }
    x = id (x);
  else
    x = id (x);
  return x + 5;
}

template <typename T> int
fallthrough (T x)
{
  int r = 0;
  switch (id (x))
    {
    case 0:
      if constexpr (std::is_integral_v<T>)
	r = id (1);
      [[fallthrough]];
    case 1:
      r += id (2);
      break;
    case 2:
      if constexpr (std::is_integral_v<T>)
	{
	  r = id (3);
	  break;
	}
      [[fallthrough]];
    default:
      r = 7;
    }
  return r;
}

template <typename T> int
with_local (T x)
{
  if constexpr (std::is_integral_v<T>)
    {
      int y = x * 2;
      return y;
    }
  return -1;
}

int
main ()
{
  if (then_only (1) != 2
      || else_only (1) != 3
      || not_a_template (1) != 4
      || not_taken (1) != 5
      || same_branches (1) != 6
      || fallthrough (0) != 3
      || fallthrough (2) != 3
      || fallthrough (5) != 7
      || with_local (4) != 8)
    __builtin_abort ();
}
