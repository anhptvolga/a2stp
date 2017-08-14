set(CLIENT_SRCS client.h
        client.cpp)

add_executable(client ${CLIENT_SRCS})
target_link_libraries(client PRIVATE bitlib utils)