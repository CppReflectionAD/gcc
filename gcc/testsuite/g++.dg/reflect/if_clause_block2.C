// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection -Wduplicated-branches -Wimplicit-fallthrough" }
// cpp_reflection_ad#269: the blocks of an `if` kept for
// std::meta::statements_of run, and warn, as without -freflection.

[[gnu::noipa]] int id (int x) { return x; }

int
same_block (int x)
{
  if (x)	// { dg-warning "this condition has identical branches" }
    { x = id (x + 1); }
  else
    { x = id (x + 1); }
  return x;
}

int
block_and_statement (int x)
{
  if (x)	// { dg-warning "this condition has identical branches" }
    { x = id (x + 2); }
  else
    x = id (x + 2);
  return x;
}

int
empty_blocks (int x)
{
  if (x)	// { dg-bogus "identical branches" }
    {}
  else
    {}
  return x;
}

int
falls_through (int x)
{
  switch (x)
    {
    case 1:
      if (id (x))	// { dg-warning "this statement may fall through" }
	{ x = id (x + 3); }
    case 2:
      return x;
    }
  return 0;
}

int
blocks (int x)
{
  if (x > 1)
    { x = id (x * 2); }
  else
    {}
  if (x > 100)
    {}
  else
    { int y = id (x); x = y + 1; }
  return x;
}

int
main ()
{
  if (same_block (1) != 2 || block_and_statement (1) != 3
      || empty_blocks (1) != 1 || falls_through (1) != 4 || blocks (2) != 5
      || blocks (0) != 1)
    __builtin_abort ();
}
