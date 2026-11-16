// { dg-do compile { target c++26 } }
// { dg-options "-freflection -Wimplicit-fallthrough -Wduplicated-branches" }
// A block that declares nothing is kept for std::meta::statements_of, but
// warnings see the same code as without -freflection.

void bar (int);
int g;

void
fallthrough_after_block (int i)
{
  switch (i)
    {
    case 1:
      { int a; }
      {
	if (i)	// { dg-warning "statement may fall through" }
	  if (i > 9)
	    bar (1);
      }
    case 2:
      bar (2);
    }
}

void
fallthrough_in_block (int i)
{
  switch (i)
    {
    case 1:
      {
	switch (i + 2)	// { dg-warning "statement may fall through" }
	  case 4:
	    bar (1);
	  case 5:
	    bar (5);
      }
      break;
    }
}

void
duplicated_nested_blocks (int i)
{
  if (i == 5)	// { dg-warning "this condition has identical branches" }
    {
      {
	{
	  g++;
	}
      }
    }
  else
    {
      {
	{
	  g++;
	}
      }
    }
}
