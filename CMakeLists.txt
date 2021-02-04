set(headers
    include/cleanuphelper.h
    include/cppflags.h
    include/cppmacros.h
    include/cppoverloadutils.h
    include/cppsignal.h
    include/cpptypesafeenum.h
    include/cpputils.h
    include/delayedconstruction.h
)

idf_component_register(INCLUDE_DIRS include SRCS ${headers})
