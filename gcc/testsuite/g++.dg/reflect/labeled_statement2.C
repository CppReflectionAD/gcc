// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection -Wno-vla -Wno-pedantic -Wno-switch-unreachable -g -gstatement-frontiers" }
// As labeled_statement1.C, with the DEBUG_BEGIN_STMTs that the parser puts
// before each statement.

#include "labeled_statement1.C"
