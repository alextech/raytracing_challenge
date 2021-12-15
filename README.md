Installation
===============

Use [vcpkg - c++ library repository](https://vcpkg.io/en/index.html)

Install catch2 dependency for unit tests:

`vcpkg install catch2:x64-windows`

To run tests:

Design Decisions
================

Some design decisions are not the only way to do this. Conflicting ideas exist. Worth trying:

* Arithmetic operations to mutate tuples themselves.
  Currently, operators always return new structs. Follows functional immutability.
  Does that create more memory? Does renderer need to have old points or only result of last transform?
  I do not know until further chapters when they get used.

* Heap vs. stack. Consider new-ing tuples.
  Currently, simple to use stack without syntax and logic difficulties of dereferencing.
  But stack has limitations if scene gets large. Also, heap would be better if other scopes
  operate on large set of tuples created elsewhere.

* Canvas coordinates are not world coordinates. Need to do (canvasHeight - pixel) to render correctly.
  Currently, coordinate correction is done by "userland" code. Not sure if this is correct, or if canvas
  should know itself how to convert world to physical coordinates.

* Logging of pixel data when potentially get unexpected results is currently done with VERBOSE preprocessor flag.
  Pixels outside of canvas range are ignored, instead of crash to still give opportunity to show what
  output looks like.