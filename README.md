# GCC with expression reflection (P4395)

This is a fork of GCC whose `p4395` branch adds expression reflection, the C++
proposal P4395 (`body_of`, `statements_of`, `operands_of`, ...).
[cpp_reflection_ad](https://github.com/CppReflectionAD/cpp_reflection_ad)
builds and tests with it, and pins it as a submodule. There are two GCC forks,
with the same reflection commits:

- [CppReflectionAD/gcc](https://github.com/CppReflectionAD/gcc/tree/p4395),
  based on upstream GCC.
- [CppReflectionAD/gcc-darwin-arm64](https://github.com/CppReflectionAD/gcc-darwin-arm64/tree/p4395),
  for macOS on Apple silicon, based on a snapshot of
  [iains/gcc-darwin-arm64](https://github.com/iains/gcc-darwin-arm64).

## Reporting a bug

The fork repositories have issues turned off. Report a bug in the reflection
support as an
[issue in cpp_reflection_ad](https://github.com/CppReflectionAD/cpp_reflection_ad/issues/new),
with a small reproducer. Bugs in the forks are tracked there under the
[`CompilerGap`](https://github.com/CppReflectionAD/cpp_reflection_ad/issues?q=label%3ACompilerGap)
label. Report bugs in the rest of GCC to [GCC](https://gcc.gnu.org/bugs/).

## Changing it

A fix is a pull request into `p4395`, merged with a merge commit.
[Bumping a compiler pin](https://github.com/CppReflectionAD/cpp_reflection_ad/blob/main/CONTRIBUTING.md#bumping-a-compiler-pin)
in cpp_reflection_ad says why, and how the two forks are kept in step.

GCC's own README is [README](README).
