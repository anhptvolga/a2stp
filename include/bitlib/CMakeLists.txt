set(BITLIB_SRCS
        bitlib.cpp
        bitlib.h)

add_library(bitlib ${BITLIB_SRCS})
target_include_directories(bitlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

#add tests
add_subdirectory(tests)