// cpp_reflection_ad#269: under -freflection, a block that declares
// nothing, and an `if` with a constant condition, are kept for
// std::meta::statements_of until they are gimplified.  The statements in
// them keep their lines, as without -freflection.

// { dg-do run { target c++26 } }
// { dg-options "--coverage -freflection" }

int n;

void
then_block (int c)
{
  if (c)			/* count(2) */
    {
      ++n;			/* count(1) */
      return;			/* count(1) */
    }
  ++n;				/* count(1) */
}

void
else_block (int c)
{
  if (c)			/* count(2) */
    ++n;			/* count(1) */
  else
    {
      return;			/* count(1) */
    }
  ++n;				/* count(1) */
}

void
nested_block (int c)
{
  {
    if (c)			/* count(2) */
      return;			/* count(1) */
  }
  {
    return;			/* count(1) */
  }
}

void
constant_if ()
{
  if (false)
    {}
  else
    return;			/* count(1) */
}

int
main ()
{
  constant_if ();
  then_block (0);
  then_block (1);
  else_block (0);
  else_block (1);
  nested_block (0);
  nested_block (1);
  if (n != 4)
    __builtin_abort ();
}

// { dg-final { run-gcov gcov-28.C } }
