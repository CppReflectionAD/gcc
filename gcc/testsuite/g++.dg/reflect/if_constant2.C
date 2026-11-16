// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection -Wreturn-type -Wimplicit-fallthrough -Wattributes" }
// cpp_reflection_ad#268: a plain `if` with a constant condition, kept for
// std::meta::statements_of, runs, and warns, as the statement its condition
// selects.

[[gnu::noipa]] int id (int x) { return x; }

struct D
{
  ~D () {}
};

// PR c++/107310
int
throws (int t)
{
  D g;
  switch (t)
    {
    case 1:
      return 1;
    }
  if (true)
    throw 1;
}				// { dg-bogus "control reaches end" }

int
then_returns (int x)
{
  if (true)
    return x + 1;
}				// { dg-bogus "control reaches end" }

int
else_returns (int x)
{
  if (false)
    {}
  else
    return x + 2;
}				// { dg-bogus "control reaches end" }

int
may_not_return (int x)
{
  if (true)
    {
      if (x)
	return x;
    }
}				// { dg-warning "control reaches end" }

int
taken (int x)
{
  if (sizeof (int) >= 2)
    x = id (x + 3);
  else
    (void) x;
  return x;
}

int
both_likely (int x)
{
  if (true)
    [[likely]] x = id (x + 5);	// { dg-warning "both branches" }
  else
    [[likely]];
  return x;
}

int
fallthrough (int x)
{
  int r = 0;
  switch (id (x))
    {
    case 0:
      if (true)
	r = id (1);
      [[fallthrough]];
    case 1:
      r += id (2);
      break;
    case 2:
      if (true)
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

int
with_local (int x)
{
  if (true)
    {
      D d;
      int y = x * 2;
      return y;
    }
  return -1;
}

int
throws_in_then (int x)
{
  if (x)
    {
      if (true)
	throw 2;
    }
  else
    x = id (x + 6);
  return x;
}

int
main ()
{
  int caught = 0;
  try
    {
      throws (0);
    }
  catch (int)
    {
      ++caught;
    }
  try
    {
      throws_in_then (1);
    }
  catch (int)
    {
      ++caught;
    }
  if (caught != 2
      || throws (1) != 1
      || then_returns (1) != 2
      || else_returns (1) != 3
      || may_not_return (4) != 4
      || taken (1) != 4
      || both_likely (1) != 6
      || fallthrough (0) != 3
      || fallthrough (2) != 3
      || fallthrough (5) != 7
      || with_local (4) != 8
      || throws_in_then (0) != 6)
    __builtin_abort ();
}
