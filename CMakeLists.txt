set(headers
    src/cleanuphelper.h
    src/color_utils.h
    src/cppbitmask.h
    src/cppflags.h
    src/cppmacros.h
    src/cppoverloadutils.h
    src/cppsignal.h
    src/cpptypesafeenum.h
    src/cpputils.h
    src/crc32builder.h
    src/delayedconstruction.h
    src/makearray.h
    src/numberparsing.h
    src/refwhenneeded.h
    src/strutils.h
)

set(sources
    src/color_utils.cpp
    src/strutils.cpp
)

set(dependencies
    expected
    fmt
)

idf_component_register(
    INCLUDE_DIRS
        src
    SRCS
        ${headers}
        ${sources}
    REQUIRES
        ${dependencies}
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
)
