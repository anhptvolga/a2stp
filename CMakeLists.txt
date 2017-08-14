cmake_minimum_required(VERSION 3.8)
project(a2stp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("-Wall")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.64 REQUIRED COMPONENTS unit_test_framework)
add_library(boost_test INTERFACE)
target_link_libraries(boost_test INTERFACE ${Boost_LIBRARIES})
target_include_directories(boost_test INTERFACE ${Boost_INCLUDE_DIRS})

add_subdirectory(include)
add_subdirectory(client)
add_subdirectory(server)