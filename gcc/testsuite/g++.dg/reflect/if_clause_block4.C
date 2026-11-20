// cpp_reflection_ad#269: under -freflection, a block that is a clause of an
// `if' is kept for std::meta::statements_of until it is gimplified.  What
// the gimplifier builds for the statements in it without a location, such
// as the predictor of a `continue', gets the location of the `if', as
// without -freflection, not that of the block's `}'.

// { dg-do compile { target c++26 } }
// { dg-options "-freflection -fdump-tree-gimple-lineno" }

int
f (int n)
{
  int s = 0;
  for (int i = 0; i < n; ++i)
    {
      if (i & 1)
	{
	  ++s;
	  continue;
	}
      s += 2;
    }
  return s;
}

// { dg-final { scan-tree-dump {if_clause_block4.C:16:7\] // predicted unlikely by continue predictor} "gimple" } }
// { dg-final { scan-tree-dump-not {if_clause_block4.C:20:[0-9]+\]} "gimple" } }
