cmake_minimum_required(VERSION 2.6)
project(easycrypto)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(easycrypto main.cpp
                         Caesar.cpp)

target_link_libraries(easycrypto gmock)

install(TARGETS easycrypto RUNTIME DESTINATION build)

add_subdirectory(test)