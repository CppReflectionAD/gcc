/* C++ code produced by gperf version 3.2.1 */
/* Command-line: gperf -o -C -E -k '1,4,5,11,14,$' -D -N find -L C++ --output-file metafns.h metafns.gperf  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 5 "metafns.gperf"

/* Copyright (C) 2025-2026 Free Software Foundation, Inc.
   Written by Jakub Jelinek <jakub@redhat.com>

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

enum metafn_code {
  METAFN_OPERATOR_OF,
  METAFN_SYMBOL_OF,
  METAFN_U8SYMBOL_OF,
  METAFN_HAS_IDENTIFIER,
  METAFN_IDENTIFIER_OF,
  METAFN_U8IDENTIFIER_OF,
  METAFN_DISPLAY_STRING_OF,
  METAFN_U8DISPLAY_STRING_OF,
  METAFN_SOURCE_LOCATION_OF,
  METAFN_TYPE_OF,
  METAFN_OBJECT_OF,
  METAFN_CONSTANT_OF,
  METAFN_IS_PUBLIC,
  METAFN_IS_PROTECTED,
  METAFN_IS_PRIVATE,
  METAFN_IS_VIRTUAL,
  METAFN_IS_PURE_VIRTUAL,
  METAFN_IS_OVERRIDE,
  METAFN_IS_FINAL,
  METAFN_IS_DELETED,
  METAFN_IS_DEFAULTED,
  METAFN_IS_USER_PROVIDED,
  METAFN_IS_USER_DECLARED,
  METAFN_IS_EXPLICIT,
  METAFN_IS_NOEXCEPT,
  METAFN_IS_BIT_FIELD,
  METAFN_IS_ENUMERATOR,
  METAFN_IS_ANNOTATION,
  METAFN_IS_CONST,
  METAFN_IS_VOLATILE,
  METAFN_IS_MUTABLE_MEMBER,
  METAFN_IS_LVALUE_REFERENCE_QUALIFIED,
  METAFN_IS_RVALUE_REFERENCE_QUALIFIED,
  METAFN_HAS_STATIC_STORAGE_DURATION,
  METAFN_HAS_THREAD_STORAGE_DURATION,
  METAFN_HAS_AUTOMATIC_STORAGE_DURATION,
  METAFN_HAS_INTERNAL_LINKAGE,
  METAFN_HAS_MODULE_LINKAGE,
  METAFN_HAS_EXTERNAL_LINKAGE,
  METAFN_HAS_C_LANGUAGE_LINKAGE,
  METAFN_HAS_LINKAGE,
  METAFN_IS_COMPLETE_TYPE,
  METAFN_IS_ENUMERABLE_TYPE,
  METAFN_IS_VARIABLE,
  METAFN_IS_TYPE,
  METAFN_IS_NAMESPACE,
  METAFN_IS_TYPE_ALIAS,
  METAFN_IS_NAMESPACE_ALIAS,
  METAFN_IS_FUNCTION,
  METAFN_IS_CONVERSION_FUNCTION,
  METAFN_IS_OPERATOR_FUNCTION,
  METAFN_IS_LITERAL_OPERATOR,
  METAFN_IS_SPECIAL_MEMBER_FUNCTION,
  METAFN_IS_CONSTRUCTOR,
  METAFN_IS_DEFAULT_CONSTRUCTOR,
  METAFN_IS_COPY_CONSTRUCTOR,
  METAFN_IS_MOVE_CONSTRUCTOR,
  METAFN_IS_ASSIGNMENT,
  METAFN_IS_COPY_ASSIGNMENT,
  METAFN_IS_MOVE_ASSIGNMENT,
  METAFN_IS_DESTRUCTOR,
  METAFN_IS_FUNCTION_PARAMETER,
  METAFN_IS_EXPLICIT_OBJECT_PARAMETER,
  METAFN_HAS_DEFAULT_ARGUMENT,
  METAFN_IS_VARARG_FUNCTION,
  METAFN_IS_TEMPLATE,
  METAFN_IS_FUNCTION_TEMPLATE,
  METAFN_IS_VARIABLE_TEMPLATE,
  METAFN_IS_CLASS_TEMPLATE,
  METAFN_IS_ALIAS_TEMPLATE,
  METAFN_IS_CONVERSION_FUNCTION_TEMPLATE,
  METAFN_IS_OPERATOR_FUNCTION_TEMPLATE,
  METAFN_IS_LITERAL_OPERATOR_TEMPLATE,
  METAFN_IS_CONSTRUCTOR_TEMPLATE,
  METAFN_IS_CONCEPT,
  METAFN_IS_VALUE,
  METAFN_IS_OBJECT,
  METAFN_IS_STRUCTURED_BINDING,
  METAFN_IS_CLASS_MEMBER,
  METAFN_IS_NAMESPACE_MEMBER,
  METAFN_IS_NONSTATIC_DATA_MEMBER,
  METAFN_IS_STATIC_MEMBER,
  METAFN_IS_BASE,
  METAFN_HAS_DEFAULT_MEMBER_INITIALIZER,
  METAFN_HAS_PARENT,
  METAFN_PARENT_OF,
  METAFN_DEALIAS,
  METAFN_HAS_TEMPLATE_ARGUMENTS,
  METAFN_TEMPLATE_OF,
  METAFN_TEMPLATE_ARGUMENTS_OF,
  METAFN_PARAMETERS_OF,
  METAFN_VARIABLE_OF,
  METAFN_RETURN_TYPE_OF,
  METAFN_HAS_BODY,
  METAFN_BODY_OF,
  METAFN_STATEMENTS_OF,
  METAFN_IS_ACCESSIBLE,
  METAFN_HAS_INACCESSIBLE_NONSTATIC_DATA_MEMBERS,
  METAFN_HAS_INACCESSIBLE_BASES,
  METAFN_HAS_INACCESSIBLE_SUBOBJECTS,
  METAFN_CURRENT_FUNCTION,
  METAFN_CURRENT_CLASS,
  METAFN_CURRENT_NAMESPACE,
  METAFN_MEMBERS_OF,
  METAFN_BASES_OF,
  METAFN_STATIC_DATA_MEMBERS_OF,
  METAFN_NONSTATIC_DATA_MEMBERS_OF,
  METAFN_SUBOBJECTS_OF,
  METAFN_ENUMERATORS_OF,
  METAFN_OFFSET_OF,
  METAFN_SIZE_OF,
  METAFN_ALIGNMENT_OF,
  METAFN_BIT_SIZE_OF,
  METAFN_EXTRACT,
  METAFN_CAN_SUBSTITUTE,
  METAFN_SUBSTITUTE,
  METAFN_REFLECT_CONSTANT,
  METAFN_REFLECT_OBJECT,
  METAFN_REFLECT_FUNCTION,
  METAFN_REFLECT_CONSTANT_STRING,
  METAFN_REFLECT_CONSTANT_ARRAY,
  METAFN_DATA_MEMBER_SPEC,
  METAFN_IS_DATA_MEMBER_SPEC,
  METAFN_DEFINE_AGGREGATE,
  METAFN_IS_VOID_TYPE,
  METAFN_IS_NULL_POINTER_TYPE,
  METAFN_IS_INTEGRAL_TYPE,
  METAFN_IS_FLOATING_POINT_TYPE,
  METAFN_IS_ARRAY_TYPE,
  METAFN_IS_POINTER_TYPE,
  METAFN_IS_LVALUE_REFERENCE_TYPE,
  METAFN_IS_RVALUE_REFERENCE_TYPE,
  METAFN_IS_MEMBER_OBJECT_POINTER_TYPE,
  METAFN_IS_MEMBER_FUNCTION_POINTER_TYPE,
  METAFN_IS_ENUM_TYPE,
  METAFN_IS_UNION_TYPE,
  METAFN_IS_CLASS_TYPE,
  METAFN_IS_FUNCTION_TYPE,
  METAFN_IS_REFLECTION_TYPE,
  METAFN_IS_REFERENCE_TYPE,
  METAFN_IS_ARITHMETIC_TYPE,
  METAFN_IS_FUNDAMENTAL_TYPE,
  METAFN_IS_OBJECT_TYPE,
  METAFN_IS_SCALAR_TYPE,
  METAFN_IS_COMPOUND_TYPE,
  METAFN_IS_MEMBER_POINTER_TYPE,
  METAFN_IS_CONST_TYPE,
  METAFN_IS_VOLATILE_TYPE,
  METAFN_IS_TRIVIALLY_COPYABLE_TYPE,
  METAFN_IS_STANDARD_LAYOUT_TYPE,
  METAFN_IS_EMPTY_TYPE,
  METAFN_IS_POLYMORPHIC_TYPE,
  METAFN_IS_ABSTRACT_TYPE,
  METAFN_IS_FINAL_TYPE,
  METAFN_IS_AGGREGATE_TYPE,
  METAFN_IS_STRUCTURAL_TYPE,
  METAFN_IS_SIGNED_TYPE,
  METAFN_IS_UNSIGNED_TYPE,
  METAFN_IS_BOUNDED_ARRAY_TYPE,
  METAFN_IS_UNBOUNDED_ARRAY_TYPE,
  METAFN_IS_SCOPED_ENUM_TYPE,
  METAFN_IS_CONSTRUCTIBLE_TYPE,
  METAFN_IS_DEFAULT_CONSTRUCTIBLE_TYPE,
  METAFN_IS_COPY_CONSTRUCTIBLE_TYPE,
  METAFN_IS_MOVE_CONSTRUCTIBLE_TYPE,
  METAFN_IS_ASSIGNABLE_TYPE,
  METAFN_IS_COPY_ASSIGNABLE_TYPE,
  METAFN_IS_MOVE_ASSIGNABLE_TYPE,
  METAFN_IS_SWAPPABLE_WITH_TYPE,
  METAFN_IS_SWAPPABLE_TYPE,
  METAFN_IS_DESTRUCTIBLE_TYPE,
  METAFN_IS_TRIVIALLY_CONSTRUCTIBLE_TYPE,
  METAFN_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TYPE,
  METAFN_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_TYPE,
  METAFN_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TYPE,
  METAFN_IS_TRIVIALLY_ASSIGNABLE_TYPE,
  METAFN_IS_TRIVIALLY_COPY_ASSIGNABLE_TYPE,
  METAFN_IS_TRIVIALLY_MOVE_ASSIGNABLE_TYPE,
  METAFN_IS_TRIVIALLY_DESTRUCTIBLE_TYPE,
  METAFN_IS_NOTHROW_CONSTRUCTIBLE_TYPE,
  METAFN_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_TYPE,
  METAFN_IS_NOTHROW_COPY_CONSTRUCTIBLE_TYPE,
  METAFN_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TYPE,
  METAFN_IS_NOTHROW_ASSIGNABLE_TYPE,
  METAFN_IS_NOTHROW_COPY_ASSIGNABLE_TYPE,
  METAFN_IS_NOTHROW_MOVE_ASSIGNABLE_TYPE,
  METAFN_IS_NOTHROW_SWAPPABLE_WITH_TYPE,
  METAFN_IS_NOTHROW_SWAPPABLE_TYPE,
  METAFN_IS_NOTHROW_DESTRUCTIBLE_TYPE,
  METAFN_IS_IMPLICIT_LIFETIME_TYPE,
  METAFN_HAS_VIRTUAL_DESTRUCTOR,
  METAFN_HAS_UNIQUE_OBJECT_REPRESENTATIONS,
  METAFN_REFERENCE_CONSTRUCTS_FROM_TEMPORARY,
  METAFN_REFERENCE_CONVERTS_FROM_TEMPORARY,
  METAFN_RANK,
  METAFN_EXTENT,
  METAFN_IS_SAME_TYPE,
  METAFN_IS_BASE_OF_TYPE,
  METAFN_IS_VIRTUAL_BASE_OF_TYPE,
  METAFN_IS_CONVERTIBLE_TYPE,
  METAFN_IS_NOTHROW_CONVERTIBLE_TYPE,
  METAFN_IS_LAYOUT_COMPATIBLE_TYPE,
  METAFN_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TYPE,
  METAFN_IS_INVOCABLE_TYPE,
  METAFN_IS_INVOCABLE_R_TYPE,
  METAFN_IS_NOTHROW_INVOCABLE_TYPE,
  METAFN_IS_NOTHROW_INVOCABLE_R_TYPE,
  METAFN_REMOVE_CONST,
  METAFN_REMOVE_VOLATILE,
  METAFN_REMOVE_CV,
  METAFN_ADD_CONST,
  METAFN_ADD_VOLATILE,
  METAFN_ADD_CV,
  METAFN_REMOVE_REFERENCE,
  METAFN_ADD_LVALUE_REFERENCE,
  METAFN_ADD_RVALUE_REFERENCE,
  METAFN_MAKE_SIGNED,
  METAFN_MAKE_UNSIGNED,
  METAFN_REMOVE_EXTENT,
  METAFN_REMOVE_ALL_EXTENTS,
  METAFN_REMOVE_POINTER,
  METAFN_ADD_POINTER,
  METAFN_REMOVE_CVREF,
  METAFN_DECAY,
  METAFN_COMMON_TYPE,
  METAFN_COMMON_REFERENCE,
  METAFN_UNDERLYING_TYPE,
  METAFN_INVOKE_RESULT,
  METAFN_UNWRAP_REFERENCE,
  METAFN_UNWRAP_REF_DECAY,
  METAFN_TUPLE_SIZE,
  METAFN_TUPLE_ELEMENT,
  METAFN_VARIANT_SIZE,
  METAFN_VARIANT_ALTERNATIVE,
  METAFN_TYPE_ORDER,
  METAFN_ANNOTATIONS_OF,
  METAFN_ANNOTATIONS_OF_WITH_TYPE,
  METAFN_IS_STATEMENT,
  METAFN_IS_COMPOUND_STATEMENT,
  METAFN_IS_EXPRESSION_STATEMENT,
  METAFN_EXPRESSION_OF,
  METAFN_IS_EXPRESSION,
  METAFN_IS_RETURN_STATEMENT,
  METAFN_IS_DECLARATION_STATEMENT,
  METAFN_IS_SIMPLE_DECLARATION,
  METAFN_DECLARED_VARIABLE_OF,
  METAFN_DECLARATORS_OF,
  METAFN_INITIALIZER_OF,
  METAFN_INITIALIZERS_OF,
  METAFN_RETURN_OPERAND_OF,
  METAFN_IS_LITERAL,
  METAFN_IS_OPERATOR_EXPRESSION,
  METAFN_IS_UNARY_OPERATOR,
  METAFN_IS_BINARY_OPERATOR,
  METAFN_IS_PREFIX,
  METAFN_IS_POSTFIX,
  METAFN_IS_FUNCTION_CALL,
  METAFN_CALLEE_OF,
  METAFN_EXPRESSION_OPERATOR_OF,
  METAFN_DECLARATION_OF,
  METAFN_OPERANDS_OF,
  METAFN_IS_CAST,
  METAFN_IS_CONSTRUCT,
  METAFN_IS_CONDITIONAL_OPERATOR,
  METAFN_CONDITION_OF,
  METAFN_TRUE_EXPRESSION_OF,
  METAFN_FALSE_EXPRESSION_OF,
  /* Special metafunctions.  */
  METAFN_ACCESS_CONTEXT_CURRENT,
  METAFN_EXCEPTION__S_EXCEPTION_CVT_TO_UTF8,
  METAFN_EXCEPTION__S_EXCEPTION_CVT_FROM_UTF8
};

enum {
  METAFN_KIND_SHIFT = 5,
  METAFN_KIND_MASK = (1 << METAFN_KIND_SHIFT) - 1
};

/* Possible return types of metafunctions.  */
enum metafn_kind_ret {
  METAFN_KIND_RET_BOOL,
  METAFN_KIND_RET_INFO,
  METAFN_KIND_RET_SIZE_T,
  METAFN_KIND_RET_MEMBER_OFFSET,
  METAFN_KIND_RET_OPERATORS,
  METAFN_KIND_RET_SOURCE_LOCATION,
  METAFN_KIND_RET_STRING_VIEW,
  METAFN_KIND_RET_U8STRING_VIEW,
  METAFN_KIND_RET_STRONG_ORDERING,
  METAFN_KIND_RET_VECTOR_INFO,
  METAFN_KIND_RET_ACCESS_CONTEXT,
  METAFN_KIND_RET_TEMPLATE_PARM,
  METAFN_KIND_RET_EXPRESSION_KIND,
};
static_assert (METAFN_KIND_RET_EXPRESSION_KIND <= (int) METAFN_KIND_MASK, "");

/* Get the metafn_kind_ret.  */
#define METAFN_KIND_RET(MINFO) \
  ((metafn_kind_ret) (((int) (MINFO)->kind) & METAFN_KIND_MASK))

/* Possible argument types of metafunctions.  */
enum metafn_kind_arg {
  METAFN_KIND_ARG_VOID = 0,
  METAFN_KIND_ARG_INFO,
  METAFN_KIND_ARG_TINFO, /* info argument which throws if not a type.  */
  METAFN_KIND_ARG_REFLECTION_RANGE,
  /* reflection_range with type infos only.  */
  METAFN_KIND_ARG_REFLECTION_RANGET,
  METAFN_KIND_ARG_INPUT_RANGE,
  METAFN_KIND_ARG_SIZE_T,
  METAFN_KIND_ARG_UNSIGNED,
  METAFN_KIND_ARG_OPERATORS,
  METAFN_KIND_ARG_ACCESS_CONTEXT,
  METAFN_KIND_ARG_DATA_MEMBER_OPTIONS,
  METAFN_KIND_ARG_TEMPLATE_PARM, /* Some other template parameter.  */
  METAFN_KIND_ARG_TEMPLATE_PARM_REF /* Reference to template parameter.  */
};
static_assert (METAFN_KIND_ARG_TEMPLATE_PARM_REF <= (int) METAFN_KIND_MASK,
	       "");

/* Get the metafn_kind_arg for argument ARGNO.  */
#define METAFN_KIND_ARG(MINFO, ARGNO) \
  ((metafn_kind_arg) (((MINFO)->kind >> ((ARGNO + 1) * METAFN_KIND_SHIFT)) \
		      & METAFN_KIND_MASK))

/* Possible sets of 0-3 arguments of metafunctions.  */
enum metafn_kind_args {
  METAFN_KIND_ARGS_VOID = METAFN_KIND_ARG_VOID,
  METAFN_KIND_ARGS_INFO = METAFN_KIND_ARG_INFO,
  METAFN_KIND_ARGS_TINFO = METAFN_KIND_ARG_TINFO,
  METAFN_KIND_ARGS_REFLECTION_RANGET = METAFN_KIND_ARG_REFLECTION_RANGET,
  METAFN_KIND_ARGS_INPUT_RANGE = METAFN_KIND_ARG_INPUT_RANGE,
  METAFN_KIND_ARGS_OPERATORS = METAFN_KIND_ARG_OPERATORS,
  METAFN_KIND_ARGS_TEMPLATE_PARM = METAFN_KIND_ARG_TEMPLATE_PARM,
  METAFN_KIND_ARGS_TEMPLATE_PARM_REF = METAFN_KIND_ARG_TEMPLATE_PARM_REF,
  METAFN_KIND_ARGS_INFO_INFO
    = (METAFN_KIND_ARG_INFO << METAFN_KIND_SHIFT) | METAFN_KIND_ARG_INFO,
  METAFN_KIND_ARGS_TINFO_TINFO
    = (METAFN_KIND_ARG_TINFO << METAFN_KIND_SHIFT) | METAFN_KIND_ARG_TINFO,
  METAFN_KIND_ARGS_TINFO_UNSIGNED
    = (METAFN_KIND_ARG_UNSIGNED << METAFN_KIND_SHIFT)
      | METAFN_KIND_ARG_TINFO,
  METAFN_KIND_ARGS_INFO_ACCESS_CONTEXT
    = (METAFN_KIND_ARG_ACCESS_CONTEXT << METAFN_KIND_SHIFT)
      | METAFN_KIND_ARG_INFO,
  METAFN_KIND_ARGS_TINFO_DATA_MEMBER_OPTIONS
    = (METAFN_KIND_ARG_DATA_MEMBER_OPTIONS << METAFN_KIND_SHIFT)
      | METAFN_KIND_ARG_TINFO,
  METAFN_KIND_ARGS_INFO_REFLECTION_RANGE
    = (METAFN_KIND_ARG_REFLECTION_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_ARG_INFO,
  METAFN_KIND_ARGS_TINFO_REFLECTION_RANGET
    = (METAFN_KIND_ARG_REFLECTION_RANGET << METAFN_KIND_SHIFT)
      | METAFN_KIND_ARG_TINFO,
  METAFN_KIND_ARGS_SIZE_T_TINFO
    = (METAFN_KIND_ARG_TINFO << METAFN_KIND_SHIFT) | METAFN_KIND_ARG_SIZE_T,
  METAFN_KIND_ARGS_TINFO_TINFO_REFLECTION_RANGET
    = (METAFN_KIND_ARG_REFLECTION_RANGET << (2 * METAFN_KIND_SHIFT))
      | METAFN_KIND_ARGS_TINFO_TINFO,
};

/* This encodes metafn_kind_ret in the low METAFN_KIND_SHIFT bits, then
   first argument metafn_kind_arg in METAFN_KIND_SHIFT bits above that,
   second argument metafn_kind_arg in METAFN_KIND_SHIFT bits above that
   and third argument metafn_kind_arg in METAFN_KIND_SHIFT bits above that.
   Missing argument is METAFN_KIND_ARG_VOID aka 0.  */
enum metafn_kind {
  METAFN_KIND_BOOL_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_BOOL,
  METAFN_KIND_BOOL_TINFO
    = (METAFN_KIND_ARGS_TINFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_BOOL,
  METAFN_KIND_BOOL_INFO_ACCESS_CONTEXT
    = (METAFN_KIND_ARGS_INFO_ACCESS_CONTEXT << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_BOOL,
  METAFN_KIND_BOOL_TINFO_TINFO
    = (METAFN_KIND_ARGS_TINFO_TINFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_BOOL,
  METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET
    = (METAFN_KIND_ARGS_TINFO_REFLECTION_RANGET << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_BOOL,
  METAFN_KIND_BOOL_TINFO_TINFO_REFLECTION_RANGET
    = (METAFN_KIND_ARGS_TINFO_TINFO_REFLECTION_RANGET << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_BOOL,
  METAFN_KIND_INFO_VOID
    = (METAFN_KIND_ARGS_VOID << METAFN_KIND_SHIFT) | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_TINFO
    = (METAFN_KIND_ARGS_TINFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_TINFO_REFLECTION_RANGET
    = (METAFN_KIND_ARGS_TINFO_REFLECTION_RANGET << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_TINFO_DATA_MEMBER_OPTIONS
    = (METAFN_KIND_ARGS_TINFO_DATA_MEMBER_OPTIONS << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_REFLECTION_RANGET
    = (METAFN_KIND_ARGS_REFLECTION_RANGET << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_BOOL_INFO_REFLECTION_RANGE
    = (METAFN_KIND_ARGS_INFO_REFLECTION_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_BOOL,
  METAFN_KIND_INFO_INFO_REFLECTION_RANGE
    = (METAFN_KIND_ARGS_INFO_REFLECTION_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_INPUT_RANGE
    = (METAFN_KIND_ARGS_INPUT_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_TEMPLATE_PARM
    = (METAFN_KIND_ARGS_TEMPLATE_PARM << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_TEMPLATE_PARM_REF
    = (METAFN_KIND_ARGS_TEMPLATE_PARM_REF << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_INFO_SIZE_T_TINFO
    = (METAFN_KIND_ARGS_SIZE_T_TINFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_INFO,
  METAFN_KIND_MEMBER_OFFSET_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_MEMBER_OFFSET,
  METAFN_KIND_OPERATORS_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_OPERATORS,
  METAFN_KIND_SIZE_T_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_SIZE_T,
  METAFN_KIND_SIZE_T_TINFO
    = (METAFN_KIND_ARGS_TINFO << METAFN_KIND_SHIFT) | METAFN_KIND_RET_SIZE_T,
  METAFN_KIND_SIZE_T_TINFO_UNSIGNED
    = (METAFN_KIND_ARGS_TINFO_UNSIGNED << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_SIZE_T,
  METAFN_KIND_SOURCE_LOCATION_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_SOURCE_LOCATION,
  METAFN_KIND_STRING_VIEW_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_STRING_VIEW,
  METAFN_KIND_STRING_VIEW_OPERATORS
    = (METAFN_KIND_ARGS_OPERATORS << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_STRING_VIEW,
  METAFN_KIND_U8STRING_VIEW_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_U8STRING_VIEW,
  METAFN_KIND_U8STRING_VIEW_OPERATORS
    = (METAFN_KIND_ARGS_OPERATORS << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_U8STRING_VIEW,
  METAFN_KIND_STRONG_ORDERING_TINFO_TINFO
    = (METAFN_KIND_ARGS_TINFO_TINFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_STRONG_ORDERING,
  METAFN_KIND_VECTOR_INFO_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_VECTOR_INFO,
  METAFN_KIND_VECTOR_INFO_INFO_INFO
    = (METAFN_KIND_ARGS_INFO_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_VECTOR_INFO,
  METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT
    = (METAFN_KIND_ARGS_INFO_ACCESS_CONTEXT << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_VECTOR_INFO,
  METAFN_KIND_TEMPLATE_PARM_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_TEMPLATE_PARM,
  METAFN_KIND_EXPRESSION_KIND_INFO
    = (METAFN_KIND_ARGS_INFO << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_EXPRESSION_KIND,
  METAFN_KIND_ACCESS_CONTEXT_VOID
    = (METAFN_KIND_ARGS_VOID << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_ACCESS_CONTEXT,
  METAFN_KIND_STRING_VIEW_INPUT_RANGE
    = (METAFN_KIND_ARGS_INPUT_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_STRING_VIEW,
  METAFN_KIND_U8STRING_VIEW_INPUT_RANGE
    = (METAFN_KIND_ARGS_INPUT_RANGE << METAFN_KIND_SHIFT)
      | METAFN_KIND_RET_U8STRING_VIEW
};
#line 499 "metafns.gperf"
struct metafn_info
{
  /* A name within "std::meta::" (or "std::meta::access_context::").  */
  const char *name;

  /* METAFN_ code.  */
  metafn_code code;

  /* METAFN_KIND_ kind of arguments and return type.  */
  metafn_kind kind;
};
/* maximum key range = 1123, duplicates = 1 */

class metafn_lookup
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct metafn_info *find (const char *str, size_t len);
};

inline unsigned int
metafn_lookup::hash (const char *str, size_t len)
{
  static const unsigned short asso_values[] =
    {
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132,    0, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132,   50,  200,  180,   85,   20,
       215,    0,    5,   50,  170,   15,  335,    0,  185,  105,
         0,  195,    0,   30,    5,  120,    0,  220,   75,  220,
         0,  470,   60, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132, 1132,
      1132, 1132, 1132, 1132, 1132, 1132, 1132
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[13])];
#if (defined __cplusplus && (__cplusplus >= 201703L || (__cplusplus >= 201103L && defined __clang__ && __clang_major__ + (__clang_minor__ >= 9) > 3))) || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 202000L && ((defined __GNUC__ && __GNUC__ >= 10) || (defined __clang__ && __clang_major__ >= 9)))
      [[fallthrough]];
#elif (defined __GNUC__ && __GNUC__ >= 7) || (defined __clang__ && __clang_major__ >= 10)
      __attribute__ ((__fallthrough__));
#endif
      /*FALLTHROUGH*/
      case 13:
      case 12:
      case 11:
        hval += asso_values[static_cast<unsigned char>(str[10])];
#if (defined __cplusplus && (__cplusplus >= 201703L || (__cplusplus >= 201103L && defined __clang__ && __clang_major__ + (__clang_minor__ >= 9) > 3))) || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 202000L && ((defined __GNUC__ && __GNUC__ >= 10) || (defined __clang__ && __clang_major__ >= 9)))
      [[fallthrough]];
#elif (defined __GNUC__ && __GNUC__ >= 7) || (defined __clang__ && __clang_major__ >= 10)
      __attribute__ ((__fallthrough__));
#endif
      /*FALLTHROUGH*/
      case 10:
      case 9:
      case 8:
      case 7:
      case 6:
      case 5:
        hval += asso_values[static_cast<unsigned char>(str[4]+1)];
#if (defined __cplusplus && (__cplusplus >= 201703L || (__cplusplus >= 201103L && defined __clang__ && __clang_major__ + (__clang_minor__ >= 9) > 3))) || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 202000L && ((defined __GNUC__ && __GNUC__ >= 10) || (defined __clang__ && __clang_major__ >= 9)))
      [[fallthrough]];
#elif (defined __GNUC__ && __GNUC__ >= 7) || (defined __clang__ && __clang_major__ >= 10)
      __attribute__ ((__fallthrough__));
#endif
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[static_cast<unsigned char>(str[3])];
#if (defined __cplusplus && (__cplusplus >= 201703L || (__cplusplus >= 201103L && defined __clang__ && __clang_major__ + (__clang_minor__ >= 9) > 3))) || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 202000L && ((defined __GNUC__ && __GNUC__ >= 10) || (defined __clang__ && __clang_major__ >= 9)))
      [[fallthrough]];
#elif (defined __GNUC__ && __GNUC__ >= 7) || (defined __clang__ && __clang_major__ >= 10)
      __attribute__ ((__fallthrough__));
#endif
      /*FALLTHROUGH*/
      case 3:
      case 2:
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0])];
        break;
    }
  return hval + asso_values[static_cast<unsigned char>(str[len - 1])];
}

const struct metafn_info *
metafn_lookup::find (const char *str, size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 270,
      MIN_WORD_LENGTH = 4,
      MAX_WORD_LENGTH = 40,
      MIN_HASH_VALUE = 9,
      MAX_HASH_VALUE = 1131
    };

#if (defined __GNUC__ && __GNUC__ + (__GNUC_MINOR__ >= 6) > 4) || (defined __clang__ && __clang_major__ >= 3)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
  static const struct metafn_info wordlist[] =
    {
#line 705 "metafns.gperf"
      {"rank", METAFN_RANK, METAFN_KIND_SIZE_T_TINFO,},
#line 766 "metafns.gperf"
      {"is_postfix", METAFN_IS_POSTFIX, METAFN_KIND_BOOL_INFO,},
#line 535 "metafns.gperf"
      {"is_noexcept", METAFN_IS_NOEXCEPT, METAFN_KIND_BOOL_INFO,},
#line 576 "metafns.gperf"
      {"is_template", METAFN_IS_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 778 "metafns.gperf"
      {"current", METAFN_ACCESS_CONTEXT_CURRENT, METAFN_KIND_ACCESS_CONTEXT_VOID,},
#line 539 "metafns.gperf"
      {"is_const", METAFN_IS_CONST, METAFN_KIND_BOOL_INFO,},
#line 585 "metafns.gperf"
      {"is_concept", METAFN_IS_CONCEPT, METAFN_KIND_BOOL_INFO,},
#line 662 "metafns.gperf"
      {"is_polymorphic_type", METAFN_IS_POLYMORPHIC_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 611 "metafns.gperf"
      {"current_function", METAFN_CURRENT_FUNCTION, METAFN_KIND_INFO_VOID,},
#line 650 "metafns.gperf"
      {"is_reference_type", METAFN_IS_REFERENCE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 566 "metafns.gperf"
      {"is_copy_constructor", METAFN_IS_COPY_CONSTRUCTOR, METAFN_KIND_BOOL_INFO,},
#line 674 "metafns.gperf"
      {"is_copy_constructible_type", METAFN_IS_COPY_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 773 "metafns.gperf"
      {"is_construct", METAFN_IS_CONSTRUCT, METAFN_KIND_BOOL_INFO,},
#line 710 "metafns.gperf"
      {"is_convertible_type", METAFN_IS_CONVERTIBLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 700 "metafns.gperf"
      {"is_implicit_lifetime_type", METAFN_IS_IMPLICIT_LIFETIME_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 751 "metafns.gperf"
      {"expression_of", METAFN_EXPRESSION_OF, METAFN_KIND_INFO_INFO,},
#line 564 "metafns.gperf"
      {"is_constructor", METAFN_IS_CONSTRUCTOR, METAFN_KIND_BOOL_INFO,},
#line 640 "metafns.gperf"
      {"is_pointer_type", METAFN_IS_POINTER_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 555 "metafns.gperf"
      {"is_type", METAFN_IS_TYPE, METAFN_KIND_BOOL_INFO,},
#line 584 "metafns.gperf"
      {"is_constructor_template", METAFN_IS_CONSTRUCTOR_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 625 "metafns.gperf"
      {"can_substitute", METAFN_CAN_SUBSTITUTE, METAFN_KIND_BOOL_INFO_REFLECTION_RANGE,},
#line 769 "metafns.gperf"
      {"expression_operator_of", METAFN_EXPRESSION_OPERATOR_OF, METAFN_KIND_OPERATORS_INFO,},
#line 711 "metafns.gperf"
      {"is_nothrow_convertible_type", METAFN_IS_NOTHROW_CONVERTIBLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 690 "metafns.gperf"
      {"is_nothrow_constructible_type", METAFN_IS_NOTHROW_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET,},
#line 695 "metafns.gperf"
      {"is_nothrow_copy_assignable_type", METAFN_IS_NOTHROW_COPY_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 624 "metafns.gperf"
      {"extract", METAFN_EXTRACT, METAFN_KIND_TEMPLATE_PARM_INFO,},
#line 615 "metafns.gperf"
      {"bases_of", METAFN_BASES_OF, METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT,},
#line 692 "metafns.gperf"
      {"is_nothrow_copy_constructible_type", METAFN_IS_NOTHROW_COPY_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 540 "metafns.gperf"
      {"is_volatile", METAFN_IS_VOLATILE, METAFN_KIND_BOOL_INFO,},
#line 635 "metafns.gperf"
      {"is_void_type", METAFN_IS_VOID_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 713 "metafns.gperf"
      {"is_pointer_interconvertible_base_of_type", METAFN_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 559 "metafns.gperf"
      {"is_function", METAFN_IS_FUNCTION, METAFN_KIND_BOOL_INFO,},
#line 691 "metafns.gperf"
      {"is_nothrow_default_constructible_type", METAFN_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 649 "metafns.gperf"
      {"is_reflection_type", METAFN_IS_REFLECTION_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 577 "metafns.gperf"
      {"is_function_template", METAFN_IS_FUNCTION_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 523 "metafns.gperf"
      {"is_public", METAFN_IS_PUBLIC, METAFN_KIND_BOOL_INFO,},
#line 560 "metafns.gperf"
      {"is_conversion_function", METAFN_IS_CONVERSION_FUNCTION, METAFN_KIND_BOOL_INFO,},
#line 636 "metafns.gperf"
      {"is_null_pointer_type", METAFN_IS_NULL_POINTER_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 599 "metafns.gperf"
      {"template_of", METAFN_TEMPLATE_OF, METAFN_KIND_INFO_INFO,},
#line 772 "metafns.gperf"
      {"is_cast", METAFN_IS_CAST, METAFN_KIND_BOOL_INFO,},
#line 581 "metafns.gperf"
      {"is_conversion_function_template", METAFN_IS_CONVERSION_FUNCTION_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 556 "metafns.gperf"
      {"is_namespace", METAFN_IS_NAMESPACE, METAFN_KIND_BOOL_INFO,},
#line 735 "metafns.gperf"
      {"common_type", METAFN_COMMON_TYPE, METAFN_KIND_INFO_REFLECTION_RANGET,},
#line 736 "metafns.gperf"
      {"common_reference", METAFN_COMMON_REFERENCE, METAFN_KIND_INFO_REFLECTION_RANGET,},
#line 765 "metafns.gperf"
      {"is_prefix", METAFN_IS_PREFIX, METAFN_KIND_BOOL_INFO,},
#line 525 "metafns.gperf"
      {"is_private", METAFN_IS_PRIVATE, METAFN_KIND_BOOL_INFO,},
#line 656 "metafns.gperf"
      {"is_member_pointer_type", METAFN_IS_MEMBER_POINTER_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 567 "metafns.gperf"
      {"is_move_constructor", METAFN_IS_MOVE_CONSTRUCTOR, METAFN_KIND_BOOL_INFO,},
#line 675 "metafns.gperf"
      {"is_move_constructible_type", METAFN_IS_MOVE_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 613 "metafns.gperf"
      {"current_namespace", METAFN_CURRENT_NAMESPACE, METAFN_KIND_INFO_VOID,},
#line 623 "metafns.gperf"
      {"bit_size_of", METAFN_BIT_SIZE_OF, METAFN_KIND_SIZE_T_INFO,},
#line 589 "metafns.gperf"
      {"is_class_member", METAFN_IS_CLASS_MEMBER, METAFN_KIND_BOOL_INFO,},
#line 672 "metafns.gperf"
      {"is_constructible_type", METAFN_IS_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET,},
#line 753 "metafns.gperf"
      {"is_return_statement", METAFN_IS_RETURN_STATEMENT, METAFN_KIND_BOOL_INFO,},
#line 716 "metafns.gperf"
      {"is_nothrow_invocable_type", METAFN_IS_NOTHROW_INVOCABLE_TYPE, METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET,},
#line 717 "metafns.gperf"
      {"is_nothrow_invocable_r_type", METAFN_IS_NOTHROW_INVOCABLE_R_TYPE, METAFN_KIND_BOOL_TINFO_TINFO_REFLECTION_RANGET,},
#line 777 "metafns.gperf"
      {"false_expression_of", METAFN_FALSE_EXPRESSION_OF, METAFN_KIND_INFO_INFO,},
#line 696 "metafns.gperf"
      {"is_nothrow_move_assignable_type", METAFN_IS_NOTHROW_MOVE_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 569 "metafns.gperf"
      {"is_copy_assignment", METAFN_IS_COPY_ASSIGNMENT, METAFN_KIND_BOOL_INFO,},
#line 693 "metafns.gperf"
      {"is_nothrow_move_constructible_type", METAFN_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 669 "metafns.gperf"
      {"is_bounded_array_type", METAFN_IS_BOUNDED_ARRAY_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 677 "metafns.gperf"
      {"is_copy_assignable_type", METAFN_IS_COPY_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 644 "metafns.gperf"
      {"is_member_function_pointer_type", METAFN_IS_MEMBER_FUNCTION_POINTER_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 586 "metafns.gperf"
      {"is_value", METAFN_IS_VALUE, METAFN_KIND_BOOL_INFO,},
#line 554 "metafns.gperf"
      {"is_variable", METAFN_IS_VARIABLE, METAFN_KIND_BOOL_INFO,},
#line 593 "metafns.gperf"
      {"is_base", METAFN_IS_BASE, METAFN_KIND_BOOL_INFO,},
#line 606 "metafns.gperf"
      {"statements_of", METAFN_STATEMENTS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 744 "metafns.gperf"
      {"variant_alternative", METAFN_VARIANT_ALTERNATIVE, METAFN_KIND_INFO_SIZE_T_TINFO,},
#line 578 "metafns.gperf"
      {"is_variable_template", METAFN_IS_VARIABLE_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 602 "metafns.gperf"
      {"variable_of", METAFN_VARIABLE_OF, METAFN_KIND_INFO_INFO,},
#line 741 "metafns.gperf"
      {"tuple_size", METAFN_TUPLE_SIZE, METAFN_KIND_SIZE_T_TINFO,},
#line 706 "metafns.gperf"
      {"extent", METAFN_EXTENT, METAFN_KIND_SIZE_T_TINFO_UNSIGNED,},
#line 742 "metafns.gperf"
      {"tuple_element", METAFN_TUPLE_ELEMENT, METAFN_KIND_INFO_SIZE_T_TINFO,},
#line 568 "metafns.gperf"
      {"is_assignment", METAFN_IS_ASSIGNMENT, METAFN_KIND_BOOL_INFO,},
#line 596 "metafns.gperf"
      {"parent_of", METAFN_PARENT_OF, METAFN_KIND_INFO_INFO,},
#line 614 "metafns.gperf"
      {"members_of", METAFN_MEMBERS_OF, METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT,},
#line 694 "metafns.gperf"
      {"is_nothrow_assignable_type", METAFN_IS_NOTHROW_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 520 "metafns.gperf"
      {"type_of", METAFN_TYPE_OF, METAFN_KIND_INFO_INFO,},
#line 699 "metafns.gperf"
      {"is_nothrow_destructible_type", METAFN_IS_NOTHROW_DESTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 745 "metafns.gperf"
      {"type_order", METAFN_TYPE_ORDER, METAFN_KIND_STRONG_ORDERING_TINFO_TINFO,},
#line 575 "metafns.gperf"
      {"is_vararg_function", METAFN_IS_VARARG_FUNCTION, METAFN_KIND_BOOL_INFO,},
#line 512 "metafns.gperf"
      {"symbol_of", METAFN_SYMBOL_OF, METAFN_KIND_STRING_VIEW_OPERATORS,},
#line 645 "metafns.gperf"
      {"is_enum_type", METAFN_IS_ENUM_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 557 "metafns.gperf"
      {"is_type_alias", METAFN_IS_TYPE_ALIAS, METAFN_KIND_BOOL_INFO,},
#line 768 "metafns.gperf"
      {"callee_of", METAFN_CALLEE_OF, METAFN_KIND_INFO_INFO,},
#line 629 "metafns.gperf"
      {"reflect_function", METAFN_REFLECT_FUNCTION, METAFN_KIND_INFO_TEMPLATE_PARM_REF,},
#line 537 "metafns.gperf"
      {"is_enumerator", METAFN_IS_ENUMERATOR, METAFN_KIND_BOOL_INFO,},
#line 707 "metafns.gperf"
      {"is_same_type", METAFN_IS_SAME_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 587 "metafns.gperf"
      {"is_object", METAFN_IS_OBJECT, METAFN_KIND_BOOL_INFO,},
#line 600 "metafns.gperf"
      {"template_arguments_of", METAFN_TEMPLATE_ARGUMENTS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 653 "metafns.gperf"
      {"is_object_type", METAFN_IS_OBJECT_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 574 "metafns.gperf"
      {"has_default_argument", METAFN_HAS_DEFAULT_ARGUMENT, METAFN_KIND_BOOL_INFO,},
#line 743 "metafns.gperf"
      {"variant_size", METAFN_VARIANT_SIZE, METAFN_KIND_SIZE_T_TINFO,},
#line 601 "metafns.gperf"
      {"parameters_of", METAFN_PARAMETERS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 590 "metafns.gperf"
      {"is_namespace_member", METAFN_IS_NAMESPACE_MEMBER, METAFN_KIND_BOOL_INFO,},
#line 708 "metafns.gperf"
      {"is_base_of_type", METAFN_IS_BASE_OF_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 571 "metafns.gperf"
      {"is_destructor", METAFN_IS_DESTRUCTOR, METAFN_KIND_BOOL_INFO,},
#line 619 "metafns.gperf"
      {"enumerators_of", METAFN_ENUMERATORS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 594 "metafns.gperf"
      {"has_default_member_initializer", METAFN_HAS_DEFAULT_MEMBER_INITIALIZER, METAFN_KIND_BOOL_INFO,},
#line 570 "metafns.gperf"
      {"is_move_assignment", METAFN_IS_MOVE_ASSIGNMENT, METAFN_KIND_BOOL_INFO,},
#line 754 "metafns.gperf"
      {"is_declaration_statement", METAFN_IS_DECLARATION_STATEMENT, METAFN_KIND_BOOL_INFO,},
#line 595 "metafns.gperf"
      {"has_parent", METAFN_HAS_PARENT, METAFN_KIND_BOOL_INFO,},
#line 678 "metafns.gperf"
      {"is_move_assignable_type", METAFN_IS_MOVE_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 762 "metafns.gperf"
      {"is_operator_expression", METAFN_IS_OPERATOR_EXPRESSION, METAFN_KIND_BOOL_INFO,},
#line 642 "metafns.gperf"
      {"is_rvalue_reference_type", METAFN_IS_RVALUE_REFERENCE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 698 "metafns.gperf"
      {"is_nothrow_swappable_type", METAFN_IS_NOTHROW_SWAPPABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 749 "metafns.gperf"
      {"is_compound_statement", METAFN_IS_COMPOUND_STATEMENT, METAFN_KIND_BOOL_INFO,},
#line 591 "metafns.gperf"
      {"is_nonstatic_data_member", METAFN_IS_NONSTATIC_DATA_MEMBER, METAFN_KIND_BOOL_INFO,},
#line 697 "metafns.gperf"
      {"is_nothrow_swappable_with_type", METAFN_IS_NOTHROW_SWAPPABLE_WITH_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 732 "metafns.gperf"
      {"add_pointer", METAFN_ADD_POINTER, METAFN_KIND_INFO_TINFO,},
#line 548 "metafns.gperf"
      {"has_module_linkage", METAFN_HAS_MODULE_LINKAGE, METAFN_KIND_BOOL_INFO,},
#line 652 "metafns.gperf"
      {"is_fundamental_type", METAFN_IS_FUNDAMENTAL_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 572 "metafns.gperf"
      {"is_function_parameter", METAFN_IS_FUNCTION_PARAMETER, METAFN_KIND_BOOL_INFO,},
#line 515 "metafns.gperf"
      {"identifier_of", METAFN_IDENTIFIER_OF, METAFN_KIND_STRING_VIEW_INFO,},
#line 511 "metafns.gperf"
      {"operator_of", METAFN_OPERATOR_OF, METAFN_KIND_OPERATORS_INFO,},
#line 771 "metafns.gperf"
      {"operands_of", METAFN_OPERANDS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 565 "metafns.gperf"
      {"is_default_constructor", METAFN_IS_DEFAULT_CONSTRUCTOR, METAFN_KIND_BOOL_INFO,},
#line 673 "metafns.gperf"
      {"is_default_constructible_type", METAFN_IS_DEFAULT_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 739 "metafns.gperf"
      {"unwrap_reference", METAFN_UNWRAP_REFERENCE, METAFN_KIND_INFO_TINFO,},
#line 712 "metafns.gperf"
      {"is_layout_compatible_type", METAFN_IS_LAYOUT_COMPATIBLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 621 "metafns.gperf"
      {"size_of", METAFN_SIZE_OF, METAFN_KIND_SIZE_T_INFO,},
#line 620 "metafns.gperf"
      {"offset_of", METAFN_OFFSET_OF, METAFN_KIND_MEMBER_OFFSET_INFO,},
#line 551 "metafns.gperf"
      {"has_linkage", METAFN_HAS_LINKAGE, METAFN_KIND_BOOL_INFO,},
#line 680 "metafns.gperf"
      {"is_swappable_type", METAFN_IS_SWAPPABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 579 "metafns.gperf"
      {"is_class_template", METAFN_IS_CLASS_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 612 "metafns.gperf"
      {"current_class", METAFN_CURRENT_CLASS, METAFN_KIND_INFO_VOID,},
#line 563 "metafns.gperf"
      {"is_special_member_function", METAFN_IS_SPECIAL_MEMBER_FUNCTION, METAFN_KIND_BOOL_INFO,},
#line 676 "metafns.gperf"
      {"is_assignable_type", METAFN_IS_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 643 "metafns.gperf"
      {"is_member_object_pointer_type", METAFN_IS_MEMBER_OBJECT_POINTER_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 524 "metafns.gperf"
      {"is_protected", METAFN_IS_PROTECTED, METAFN_KIND_BOOL_INFO,},
#line 553 "metafns.gperf"
      {"is_enumerable_type", METAFN_IS_ENUMERABLE_TYPE, METAFN_KIND_BOOL_INFO,},
#line 654 "metafns.gperf"
      {"is_scalar_type", METAFN_IS_SCALAR_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 659 "metafns.gperf"
      {"is_trivially_copyable_type", METAFN_IS_TRIVIALLY_COPYABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 748 "metafns.gperf"
      {"is_statement", METAFN_IS_STATEMENT, METAFN_KIND_BOOL_INFO,},
#line 603 "metafns.gperf"
      {"return_type_of", METAFN_RETURN_TYPE_OF, METAFN_KIND_INFO_INFO,},
#line 682 "metafns.gperf"
      {"is_trivially_constructible_type", METAFN_IS_TRIVIALLY_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET,},
#line 541 "metafns.gperf"
      {"is_mutable_member", METAFN_IS_MUTABLE_MEMBER, METAFN_KIND_BOOL_INFO,},
#line 687 "metafns.gperf"
      {"is_trivially_copy_assignable_type", METAFN_IS_TRIVIALLY_COPY_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 684 "metafns.gperf"
      {"is_trivially_copy_constructible_type", METAFN_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 758 "metafns.gperf"
      {"initializer_of", METAFN_INITIALIZER_OF, METAFN_KIND_INFO_INFO,},
#line 522 "metafns.gperf"
      {"constant_of", METAFN_CONSTANT_OF, METAFN_KIND_INFO_INFO,},
#line 665 "metafns.gperf"
      {"is_aggregate_type", METAFN_IS_AGGREGATE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 651 "metafns.gperf"
      {"is_arithmetic_type", METAFN_IS_ARITHMETIC_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 546 "metafns.gperf"
      {"has_automatic_storage_duration", METAFN_HAS_AUTOMATIC_STORAGE_DURATION, METAFN_KIND_BOOL_INFO,},
#line 627 "metafns.gperf"
      {"reflect_constant", METAFN_REFLECT_CONSTANT, METAFN_KIND_INFO_TEMPLATE_PARM,},
#line 638 "metafns.gperf"
      {"is_floating_point_type", METAFN_IS_FLOATING_POINT_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 518 "metafns.gperf"
      {"u8display_string_of", METAFN_U8DISPLAY_STRING_OF, METAFN_KIND_U8STRING_VIEW_INFO,},
#line 517 "metafns.gperf"
      {"display_string_of", METAFN_DISPLAY_STRING_OF, METAFN_KIND_STRING_VIEW_INFO,},
#line 618 "metafns.gperf"
      {"subobjects_of", METAFN_SUBOBJECTS_OF, METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT,},
#line 737 "metafns.gperf"
      {"underlying_type", METAFN_UNDERLYING_TYPE, METAFN_KIND_INFO_TINFO,},
#line 725 "metafns.gperf"
      {"add_lvalue_reference", METAFN_ADD_LVALUE_REFERENCE, METAFN_KIND_INFO_TINFO,},
#line 538 "metafns.gperf"
      {"is_annotation", METAFN_IS_ANNOTATION, METAFN_KIND_BOOL_INFO,},
#line 521 "metafns.gperf"
      {"object_of", METAFN_OBJECT_OF, METAFN_KIND_INFO_INFO,},
#line 726 "metafns.gperf"
      {"add_rvalue_reference", METAFN_ADD_RVALUE_REFERENCE, METAFN_KIND_INFO_TINFO,},
#line 714 "metafns.gperf"
      {"is_invocable_type", METAFN_IS_INVOCABLE_TYPE, METAFN_KIND_BOOL_TINFO_REFLECTION_RANGET,},
#line 666 "metafns.gperf"
      {"is_structural_type", METAFN_IS_STRUCTURAL_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 729 "metafns.gperf"
      {"remove_extent", METAFN_REMOVE_EXTENT, METAFN_KIND_INFO_TINFO,},
#line 715 "metafns.gperf"
      {"is_invocable_r_type", METAFN_IS_INVOCABLE_R_TYPE, METAFN_KIND_BOOL_TINFO_TINFO_REFLECTION_RANGET,},
#line 724 "metafns.gperf"
      {"remove_reference", METAFN_REMOVE_REFERENCE, METAFN_KIND_INFO_TINFO,},
#line 733 "metafns.gperf"
      {"remove_cvref", METAFN_REMOVE_CVREF, METAFN_KIND_INFO_TINFO,},
#line 558 "metafns.gperf"
      {"is_namespace_alias", METAFN_IS_NAMESPACE_ALIAS, METAFN_KIND_BOOL_INFO,},
#line 681 "metafns.gperf"
      {"is_destructible_type", METAFN_IS_DESTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 528 "metafns.gperf"
      {"is_override", METAFN_IS_OVERRIDE, METAFN_KIND_BOOL_INFO,},
#line 774 "metafns.gperf"
      {"is_conditional_operator", METAFN_IS_CONDITIONAL_OPERATOR, METAFN_KIND_BOOL_INFO,},
#line 731 "metafns.gperf"
      {"remove_pointer", METAFN_REMOVE_POINTER, METAFN_KIND_INFO_TINFO,},
#line 630 "metafns.gperf"
      {"reflect_constant_string", METAFN_REFLECT_CONSTANT_STRING, METAFN_KIND_INFO_INPUT_RANGE,},
#line 641 "metafns.gperf"
      {"is_lvalue_reference_type", METAFN_IS_LVALUE_REFERENCE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 721 "metafns.gperf"
      {"add_const", METAFN_ADD_CONST, METAFN_KIND_INFO_TINFO,},
#line 688 "metafns.gperf"
      {"is_trivially_move_assignable_type", METAFN_IS_TRIVIALLY_MOVE_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 530 "metafns.gperf"
      {"is_deleted", METAFN_IS_DELETED, METAFN_KIND_BOOL_INFO,},
#line 685 "metafns.gperf"
      {"is_trivially_move_constructible_type", METAFN_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 531 "metafns.gperf"
      {"is_defaulted", METAFN_IS_DEFAULTED, METAFN_KIND_BOOL_INFO,},
#line 633 "metafns.gperf"
      {"is_data_member_spec", METAFN_IS_DATA_MEMBER_SPEC, METAFN_KIND_BOOL_INFO,},
#line 626 "metafns.gperf"
      {"substitute", METAFN_SUBSTITUTE, METAFN_KIND_INFO_INFO_REFLECTION_RANGE,},
#line 671 "metafns.gperf"
      {"is_scoped_enum_type", METAFN_IS_SCOPED_ENUM_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 527 "metafns.gperf"
      {"is_pure_virtual", METAFN_IS_PURE_VIRTUAL, METAFN_KIND_BOOL_INFO,},
#line 767 "metafns.gperf"
      {"is_function_call", METAFN_IS_FUNCTION_CALL, METAFN_KIND_BOOL_INFO,},
#line 588 "metafns.gperf"
      {"is_structured_binding", METAFN_IS_STRUCTURED_BINDING, METAFN_KIND_BOOL_INFO,},
#line 667 "metafns.gperf"
      {"is_signed_type", METAFN_IS_SIGNED_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 561 "metafns.gperf"
      {"is_operator_function", METAFN_IS_OPERATOR_FUNCTION, METAFN_KIND_BOOL_INFO,},
#line 543 "metafns.gperf"
      {"is_rvalue_reference_qualified", METAFN_IS_RVALUE_REFERENCE_QUALIFIED, METAFN_KIND_BOOL_INFO,},
#line 533 "metafns.gperf"
      {"is_user_declared", METAFN_IS_USER_DECLARED, METAFN_KIND_BOOL_INFO,},
#line 544 "metafns.gperf"
      {"has_static_storage_duration", METAFN_HAS_STATIC_STORAGE_DURATION, METAFN_KIND_BOOL_INFO,},
#line 582 "metafns.gperf"
      {"is_operator_function_template", METAFN_IS_OPERATOR_FUNCTION_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 534 "metafns.gperf"
      {"is_explicit", METAFN_IS_EXPLICIT, METAFN_KIND_BOOL_INFO,},
#line 661 "metafns.gperf"
      {"is_empty_type", METAFN_IS_EMPTY_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 580 "metafns.gperf"
      {"is_alias_template", METAFN_IS_ALIAS_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 720 "metafns.gperf"
      {"remove_cv", METAFN_REMOVE_CV, METAFN_KIND_INFO_TINFO,},
#line 607 "metafns.gperf"
      {"is_accessible", METAFN_IS_ACCESSIBLE, METAFN_KIND_BOOL_INFO_ACCESS_CONTEXT,},
#line 770 "metafns.gperf"
      {"declaration_of", METAFN_DECLARATION_OF, METAFN_KIND_INFO_INFO,},
#line 752 "metafns.gperf"
      {"is_expression", METAFN_IS_EXPRESSION, METAFN_KIND_BOOL_INFO,},
#line 657 "metafns.gperf"
      {"is_const_type", METAFN_IS_CONST_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 552 "metafns.gperf"
      {"is_complete_type", METAFN_IS_COMPLETE_TYPE, METAFN_KIND_BOOL_INFO,},
#line 723 "metafns.gperf"
      {"add_cv", METAFN_ADD_CV, METAFN_KIND_INFO_TINFO,},
#line 686 "metafns.gperf"
      {"is_trivially_assignable_type", METAFN_IS_TRIVIALLY_ASSIGNABLE_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 728 "metafns.gperf"
      {"make_unsigned", METAFN_MAKE_UNSIGNED, METAFN_KIND_INFO_TINFO,},
#line 776 "metafns.gperf"
      {"true_expression_of", METAFN_TRUE_EXPRESSION_OF, METAFN_KIND_INFO_INFO,},
#line 628 "metafns.gperf"
      {"reflect_object", METAFN_REFLECT_OBJECT, METAFN_KIND_INFO_TEMPLATE_PARM_REF,},
#line 529 "metafns.gperf"
      {"is_final", METAFN_IS_FINAL, METAFN_KIND_BOOL_INFO,},
#line 718 "metafns.gperf"
      {"remove_const", METAFN_REMOVE_CONST, METAFN_KIND_INFO_TINFO,},
#line 679 "metafns.gperf"
      {"is_swappable_with_type", METAFN_IS_SWAPPABLE_WITH_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 689 "metafns.gperf"
      {"is_trivially_destructible_type", METAFN_IS_TRIVIALLY_DESTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 592 "metafns.gperf"
      {"is_static_member", METAFN_IS_STATIC_MEMBER, METAFN_KIND_BOOL_INFO,},
#line 759 "metafns.gperf"
      {"initializers_of", METAFN_INITIALIZERS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 750 "metafns.gperf"
      {"is_expression_statement", METAFN_IS_EXPRESSION_STATEMENT, METAFN_KIND_BOOL_INFO,},
#line 683 "metafns.gperf"
      {"is_trivially_default_constructible_type", METAFN_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 658 "metafns.gperf"
      {"is_volatile_type", METAFN_IS_VOLATILE_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 648 "metafns.gperf"
      {"is_function_type", METAFN_IS_FUNCTION_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 514 "metafns.gperf"
      {"has_identifier", METAFN_HAS_IDENTIFIER, METAFN_KIND_BOOL_INFO,},
#line 760 "metafns.gperf"
      {"return_operand_of", METAFN_RETURN_OPERAND_OF, METAFN_KIND_INFO_INFO,},
#line 573 "metafns.gperf"
      {"is_explicit_object_parameter", METAFN_IS_EXPLICIT_OBJECT_PARAMETER, METAFN_KIND_BOOL_INFO,},
#line 730 "metafns.gperf"
      {"remove_all_extents", METAFN_REMOVE_ALL_EXTENTS, METAFN_KIND_INFO_TINFO,},
#line 562 "metafns.gperf"
      {"is_literal_operator", METAFN_IS_LITERAL_OPERATOR, METAFN_KIND_BOOL_INFO,},
#line 549 "metafns.gperf"
      {"has_external_linkage", METAFN_HAS_EXTERNAL_LINKAGE, METAFN_KIND_BOOL_INFO,},
#line 583 "metafns.gperf"
      {"is_literal_operator_template", METAFN_IS_LITERAL_OPERATOR_TEMPLATE, METAFN_KIND_BOOL_INFO,},
#line 709 "metafns.gperf"
      {"is_virtual_base_of_type", METAFN_IS_VIRTUAL_BASE_OF_TYPE, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 526 "metafns.gperf"
      {"is_virtual", METAFN_IS_VIRTUAL, METAFN_KIND_BOOL_INFO,},
#line 647 "metafns.gperf"
      {"is_class_type", METAFN_IS_CLASS_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 634 "metafns.gperf"
      {"define_aggregate", METAFN_DEFINE_AGGREGATE, METAFN_KIND_INFO_INFO_REFLECTION_RANGE,},
#line 738 "metafns.gperf"
      {"invoke_result", METAFN_INVOKE_RESULT, METAFN_KIND_INFO_TINFO_REFLECTION_RANGET,},
#line 757 "metafns.gperf"
      {"declarators_of", METAFN_DECLARATORS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 763 "metafns.gperf"
      {"is_unary_operator", METAFN_IS_UNARY_OPERATOR, METAFN_KIND_BOOL_INFO,},
#line 670 "metafns.gperf"
      {"is_unbounded_array_type", METAFN_IS_UNBOUNDED_ARRAY_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 632 "metafns.gperf"
      {"data_member_spec", METAFN_DATA_MEMBER_SPEC, METAFN_KIND_INFO_TINFO_DATA_MEMBER_OPTIONS,},
#line 622 "metafns.gperf"
      {"alignment_of", METAFN_ALIGNMENT_OF, METAFN_KIND_SIZE_T_INFO,},
#line 722 "metafns.gperf"
      {"add_volatile", METAFN_ADD_VOLATILE, METAFN_KIND_INFO_TINFO,},
#line 701 "metafns.gperf"
      {"has_virtual_destructor", METAFN_HAS_VIRTUAL_DESTRUCTOR, METAFN_KIND_BOOL_TINFO,},
#line 516 "metafns.gperf"
      {"u8identifier_of", METAFN_U8IDENTIFIER_OF, METAFN_KIND_U8STRING_VIEW_INFO,},
#line 764 "metafns.gperf"
      {"is_binary_operator", METAFN_IS_BINARY_OPERATOR, METAFN_KIND_BOOL_INFO,},
#line 616 "metafns.gperf"
      {"static_data_members_of", METAFN_STATIC_DATA_MEMBERS_OF, METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT,},
#line 542 "metafns.gperf"
      {"is_lvalue_reference_qualified", METAFN_IS_LVALUE_REFERENCE_QUALIFIED, METAFN_KIND_BOOL_INFO,},
#line 550 "metafns.gperf"
      {"has_c_language_linkage", METAFN_HAS_C_LANGUAGE_LINKAGE, METAFN_KIND_BOOL_INFO,},
#line 663 "metafns.gperf"
      {"is_abstract_type", METAFN_IS_ABSTRACT_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 513 "metafns.gperf"
      {"u8symbol_of", METAFN_U8SYMBOL_OF, METAFN_KIND_U8STRING_VIEW_OPERATORS,},
#line 545 "metafns.gperf"
      {"has_thread_storage_duration", METAFN_HAS_THREAD_STORAGE_DURATION, METAFN_KIND_BOOL_INFO,},
#line 604 "metafns.gperf"
      {"has_body", METAFN_HAS_BODY, METAFN_KIND_BOOL_INFO,},
#line 704 "metafns.gperf"
      {"reference_converts_from_temporary", METAFN_REFERENCE_CONVERTS_FROM_TEMPORARY, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 761 "metafns.gperf"
      {"is_literal", METAFN_IS_LITERAL, METAFN_KIND_BOOL_INFO,},
#line 655 "metafns.gperf"
      {"is_compound_type", METAFN_IS_COMPOUND_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 519 "metafns.gperf"
      {"source_location_of", METAFN_SOURCE_LOCATION_OF, METAFN_KIND_SOURCE_LOCATION_INFO,},
#line 746 "metafns.gperf"
      {"annotations_of", METAFN_ANNOTATIONS_OF, METAFN_KIND_VECTOR_INFO_INFO,},
#line 747 "metafns.gperf"
      {"annotations_of_with_type", METAFN_ANNOTATIONS_OF_WITH_TYPE, METAFN_KIND_VECTOR_INFO_INFO_INFO,},
#line 727 "metafns.gperf"
      {"make_signed", METAFN_MAKE_SIGNED, METAFN_KIND_INFO_TINFO,},
#line 779 "metafns.gperf"
      {"_S_exception_cvt_to_utf8", METAFN_EXCEPTION__S_EXCEPTION_CVT_TO_UTF8, METAFN_KIND_U8STRING_VIEW_INPUT_RANGE,},
#line 780 "metafns.gperf"
      {"_S_exception_cvt_from_utf8", METAFN_EXCEPTION__S_EXCEPTION_CVT_FROM_UTF8, METAFN_KIND_STRING_VIEW_INPUT_RANGE,},
#line 598 "metafns.gperf"
      {"has_template_arguments", METAFN_HAS_TEMPLATE_ARGUMENTS, METAFN_KIND_BOOL_INFO,},
#line 617 "metafns.gperf"
      {"nonstatic_data_members_of", METAFN_NONSTATIC_DATA_MEMBERS_OF, METAFN_KIND_VECTOR_INFO_INFO_ACCESS_CONTEXT,},
#line 605 "metafns.gperf"
      {"body_of", METAFN_BODY_OF, METAFN_KIND_INFO_INFO,},
#line 703 "metafns.gperf"
      {"reference_constructs_from_temporary", METAFN_REFERENCE_CONSTRUCTS_FROM_TEMPORARY, METAFN_KIND_BOOL_TINFO_TINFO,},
#line 660 "metafns.gperf"
      {"is_standard_layout_type", METAFN_IS_STANDARD_LAYOUT_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 775 "metafns.gperf"
      {"condition_of", METAFN_CONDITION_OF, METAFN_KIND_INFO_INFO,},
#line 639 "metafns.gperf"
      {"is_array_type", METAFN_IS_ARRAY_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 719 "metafns.gperf"
      {"remove_volatile", METAFN_REMOVE_VOLATILE, METAFN_KIND_INFO_TINFO,},
#line 702 "metafns.gperf"
      {"has_unique_object_representations", METAFN_HAS_UNIQUE_OBJECT_REPRESENTATIONS, METAFN_KIND_BOOL_TINFO,},
#line 664 "metafns.gperf"
      {"is_final_type", METAFN_IS_FINAL_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 536 "metafns.gperf"
      {"is_bit_field", METAFN_IS_BIT_FIELD, METAFN_KIND_BOOL_INFO,},
#line 597 "metafns.gperf"
      {"dealias", METAFN_DEALIAS, METAFN_KIND_INFO_INFO,},
#line 740 "metafns.gperf"
      {"unwrap_ref_decay", METAFN_UNWRAP_REF_DECAY, METAFN_KIND_INFO_TINFO,},
#line 631 "metafns.gperf"
      {"reflect_constant_array", METAFN_REFLECT_CONSTANT_ARRAY, METAFN_KIND_INFO_INPUT_RANGE,},
#line 756 "metafns.gperf"
      {"declared_variable_of", METAFN_DECLARED_VARIABLE_OF, METAFN_KIND_INFO_INFO,},
#line 532 "metafns.gperf"
      {"is_user_provided", METAFN_IS_USER_PROVIDED, METAFN_KIND_BOOL_INFO,},
#line 755 "metafns.gperf"
      {"is_simple_declaration", METAFN_IS_SIMPLE_DECLARATION, METAFN_KIND_BOOL_INFO,},
#line 637 "metafns.gperf"
      {"is_integral_type", METAFN_IS_INTEGRAL_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 609 "metafns.gperf"
      {"has_inaccessible_bases", METAFN_HAS_INACCESSIBLE_BASES, METAFN_KIND_BOOL_INFO_ACCESS_CONTEXT,},
#line 610 "metafns.gperf"
      {"has_inaccessible_subobjects", METAFN_HAS_INACCESSIBLE_SUBOBJECTS, METAFN_KIND_BOOL_INFO_ACCESS_CONTEXT,},
#line 646 "metafns.gperf"
      {"is_union_type", METAFN_IS_UNION_TYPE, METAFN_KIND_BOOL_TINFO,},
#line 608 "metafns.gperf"
      {"has_inaccessible_nonstatic_data_members", METAFN_HAS_INACCESSIBLE_NONSTATIC_DATA_MEMBERS, METAFN_KIND_BOOL_INFO_ACCESS_CONTEXT,},
#line 734 "metafns.gperf"
      {"decay", METAFN_DECAY, METAFN_KIND_INFO_TINFO,},
#line 547 "metafns.gperf"
      {"has_internal_linkage", METAFN_HAS_INTERNAL_LINKAGE, METAFN_KIND_BOOL_INFO,},
#line 668 "metafns.gperf"
      {"is_unsigned_type", METAFN_IS_UNSIGNED_TYPE, METAFN_KIND_BOOL_TINFO,}
    };
#if (defined __GNUC__ && __GNUC__ + (__GNUC_MINOR__ >= 6) > 4) || (defined __clang__ && __clang_major__ >= 3)
#pragma GCC diagnostic pop
#endif

  static const short lookup[] =
    {
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,    1,    2,   -1,   -1,   -1,   -1,    3,
        -1,   -1,   -1,   -1,   -1,    4,   -1,   -1,
        -1,   -1,   -1,    5,   -1,    6,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,    7,   -1,
        -1,   -1,   -1,   -1,   -1,    8,    9,   -1,
        10,   -1,   11,   12,   -1,   13,   14,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   15,   16,
        17,   -1,   18,   19,   20,   -1,   -1,   21,
        -1,   -1,   -1,   -1,   22,   -1,   23,   -1,
        24,   25,   26,   27,   -1,   28,   29,   -1,
        -1,   30,   31,   32,   33,   -1,   -1,   -1,
        -1,   -1,   -1,   34,   -1,   -1,   -1,   35,
        -1,   -1,   36,   -1,   -1,   37,   38,   39,
        -1,   -1,   -1,   40,   41,   -1,   -1,   -1,
        42,   -1,   -1,   -1,   -1,   43,   -1,   -1,
        44,   45,   -1,   46,   -1,   47,   -1,   48,
        49,   -1,   -1,   -1,   50,   -1,   -1,   -1,
        51,   52,   -1,   -1,   53,   54,   -1,   55,
        -1,   56,   -1,   57,   -1,   58,   59,   -1,
        60,   -1,   61,   -1,   -1,   62,   -1,   63,
        -1,   -1,   64,   -1,   -1,   -1,   -1,   -1,
        65,   66,   67,   68,   69,   -1,   -1,   -1,
        70,   71,   -1,   72,   -1,   -1,   -1,   -1,
        73,   74,   75,   76,   77,   78,   -1,   79,
        -1,   -1,   80,   81,   -1,   -1,   82,   83,
        84,   -1,   85,   -1,   86,   -1,   -1,   -1,
        87,   -1,   -1,   -1,   -1,   -1,   -1,   88,
        -1,   89,   -1,   -1,   90,   91,   -1,   92,
        93,   94,   95,   -1,   -1,   96,   97,   98,
        -1,   -1,   99,  100,  101,   -1,   -1,  102,
        -1,   -1,   -1,  103,   -1,  104,  105,  106,
        -1,   -1,  107,  108,   -1,   -1,   -1,   -1,
        -1,  109,   -1,   -1,   -1,   -1,   -1,   -1,
       110,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  111,   -1,  112,   -1,  113,
        -1,   -1, -578, -156,   -2,   -1,   -1,   -1,
       116,   -1,  117,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  118,   -1,
        -1,   -1,  119,   -1,  120,   -1,  121,   -1,
       122,  123,   -1,   -1,   -1,   -1,  124,  125,
        -1,   -1,  126,   -1,  127,  128,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  129,  130,  131,   -1,  132,  133,
        -1,  134,   -1,  135,  136,  137,   -1,   -1,
       138,   -1,   -1,  139,   -1,  140,  141,  142,
        -1,  143,   -1,   -1,   -1,   -1,   -1,  144,
       145,   -1,  146,   -1,   -1,  147,   -1,   -1,
        -1,   -1,   -1,  148,   -1,  149,   -1,   -1,
        -1,   -1,  150,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  151,   -1,   -1,   -1,   -1,   -1,
       152,  153,   -1,  154,  155,   -1,   -1,   -1,
        -1,  156,  157,   -1,  158,  159,  160,   -1,
       161,  162,   -1,  163,  164,   -1,   -1,   -1,
       165,  166,   -1,   -1,   -1,   -1,  167,   -1,
        -1,   -1,  168,   -1,  169,  170,  171,   -1,
       172,   -1,   -1,   -1,   -1,   -1,  173,   -1,
        -1,   -1,  174,  175,  176,   -1,   -1,   -1,
        -1,  177,   -1,   -1,  178,  179,   -1,   -1,
        -1,  180,   -1,  181,  182,   -1,  183,   -1,
       184,   -1,  185,   -1,   -1,   -1,  186,   -1,
       187,   -1,   -1,   -1,  188,  189,   -1,   -1,
        -1,  190,   -1,   -1,   -1,   -1,  191,   -1,
        -1,  192,   -1,   -1,   -1,   -1,  193,   -1,
       194,   -1,   -1,   -1,   -1,  195,   -1,   -1,
        -1,   -1,  196,   -1,   -1,   -1,   -1,   -1,
       197,   -1,   -1,   -1,  198,   -1,   -1,   -1,
       199,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  200,   -1,   -1,  201,  202,   -1,
        -1,   -1,  203,   -1,   -1,  204,  205,   -1,
       206,   -1,   -1,   -1,   -1,  207,   -1,   -1,
       208,   -1,   -1,  209,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  210,   -1,   -1,   -1,   -1,
       211,  212,  213,   -1,   -1,  214,   -1,   -1,
        -1,   -1,  215,   -1,  216,   -1,   -1,  217,
        -1,   -1,  218,   -1,  219,  220,   -1,   -1,
       221,  222,   -1,   -1,  223,  224,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  225,
        -1,   -1,   -1,   -1,  226,   -1,   -1,  227,
        -1,   -1,  228,   -1,   -1,   -1,  229,   -1,
        -1,   -1,   -1,   -1,   -1,  230,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  231,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  232,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  233,
       234,   -1,   -1,   -1,   -1,   -1,  235,   -1,
        -1,   -1,   -1,  236,   -1,   -1,   -1,   -1,
        -1,   -1,  237,   -1,   -1,   -1,   -1,   -1,
       238,   -1,  239,  240,   -1,   -1,   -1,   -1,
       241,   -1,  242,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  243,
        -1,  244,  245,   -1,   -1,  246,   -1,  247,
        -1,   -1,  248,   -1,   -1,  249,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  250,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  251,   -1,
       252,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  253,   -1,   -1,   -1,   -1,  254,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  255,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,
        -1,   -1,  257,  258,   -1,   -1,  259,   -1,
        -1,   -1,   -1,   -1,  260,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  261,   -1,   -1,   -1,   -1,
       262,   -1,   -1,   -1,   -1,   -1,  263,   -1,
        -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,
        -1,  265,   -1,   -1,   -1,   -1,   -1,  266,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  267,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  268,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  269
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          int index = lookup[key];

          if (index >= 0)
            {
              const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
          else if (index < -TOTAL_KEYWORDS)
            {
              int offset = - 1 - TOTAL_KEYWORDS - index;
              const struct metafn_info *wordptr = &wordlist[TOTAL_KEYWORDS + lookup[offset]];
              const struct metafn_info *wordendptr = wordptr + -lookup[offset + 1];

              while (wordptr < wordendptr)
                {
                  const char *s = wordptr->name;

                  if (*str == *s && !strcmp (str + 1, s + 1))
                    return wordptr;
                  wordptr++;
                }
            }
        }
    }
  return static_cast<struct metafn_info *> (0);
}
