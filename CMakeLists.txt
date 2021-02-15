set(headers
    src/cleanuphelper.h
    src/crc32builder.h
    src/cppflags.h
    src/cppmacros.h
    src/cppoverloadutils.h
    src/cppsignal.h
    src/cpptypesafeenum.h
    src/cpputils.h
    src/delayedconstruction.h
    src/strutils.h
)

set(sources
    src/strutils.cpp
)

idf_component_register(INCLUDE_DIRS src SRCS ${headers} ${sources})
