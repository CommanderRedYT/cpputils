#pragma once

// Collection of useful macros to make C++ code prettier

/*
   Avoid "unused parameter" warnings
*/
#define CPP_UNUSED(x) (void)x;

/* These two macros make it possible to turn the builtin line expander into a
 * string literal. */
#define CPP_STRINGIFY2(x) #x
#define CPP_STRINGIFY(x) CPP_STRINGIFY2(x)

/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).
*/
#define CPP_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;
#define CPP_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;
#define CPP_DISABLE_COPY_MOVE(Class) \
    CPP_DISABLE_COPY(Class) \
    CPP_DISABLE_MOVE(Class)
