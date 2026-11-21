// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -fdump-tree-gimple" }
// cpp_reflection_ad#269: a block that is the then or else statement of an
// `if` with a constant condition, and has no side effects, doesn't keep
// the `if` in the GIMPLE, as without -freflection.

int
empty_then (int x)
{
  if (false)
    {}
  else
    return x + 2;
}

int
empty_else (int x)
{
  if (true)
    return x;
  else
    {}
}

int
nested_empty (int x)
{
  if (false)
    { {} }
  else
    return x + 2;
}

int
null_statement (int x)
{
  if (false)
    { ; }
  else
    return x + 2;
}

int
bare_null_statement (int x)
{
  if (false)
    ;
  else
    return x + 2;
}

// { dg-final { scan-tree-dump-not "if \\(\[01\] != 0\\)" "gimple" } }
// { dg-final { scan-tree-dump-not "__builtin_unreachable" "gimple" } }
