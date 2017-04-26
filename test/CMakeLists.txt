cmake_minimum_required(VERSION 2.6)
project(easycrypto)

set(CMAKE_CXX_STANDARD 11)

include_directories(../include)

add_executable(tests main.cpp
                     SimpleSubstitutionTest.cpp
                     #CaesarTest.cpp
                     #../Caesar.cpp
                     )

target_link_libraries(tests gmock)

install(TARGETS tests RUNTIME DESTINATION build)