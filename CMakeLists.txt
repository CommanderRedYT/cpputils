set(headers
    src/cleanuphelper.h
    src/cppbitmask.h
    src/crc32builder.h
    src/cppflags.h
    src/cppmacros.h
    src/cppoverloadutils.h
    src/cppsignal.h
    src/cpptypesafeenum.h
    src/cpputils.h
    src/delayedconstruction.h
    src/numberparsing.h
    src/refwhenneeded.h
    src/strutils.h
)

set(sources
    src/strutils.cpp
)

set(dependencies
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
