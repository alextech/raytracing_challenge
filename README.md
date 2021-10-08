Installation
===============

Use [vcpkg - c++ library repository](https://vcpkg.io/en/index.html)

Install catch2 dependency for unit tests:

`vcpkg install catch2:x64-windows`

To run tests:

Design Decisions
================

Some design decisions are not the only way to do this. Conflicting ideas exist. Worth trying:
* Member functions instead of friend functions for operators.
  Friend function seem more fitting at the moment, instead of adding functionality to struct, 
  because currently structs are treated as immutables. 
  So the sense is, something external is reading them and returns another one.

  But maybe worth more to use traditional OOP style member operators.

* Arithmetic operations to mutate tuples themselves.
  Currently, operators always return new structs. Follows functional immutability.
  Does that create more memory? Does renderer need to have old points or only result of last transform?
  I do not know until further chapters when they get used.

* Heap vs. stack. Consider new-ing tuples.
  Currently, simple to use stack without syntax and logic difficulties of dereferencing.
  But stack has limitations if scene gets large. Also, heap would be better if other scopes
  operate on large set of tuples created elsewhere.