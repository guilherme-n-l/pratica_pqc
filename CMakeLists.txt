cmake_minimum_required(VERSION 3.10)
project(liboqs_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{LIBOQS_INCLUDE_DIR})
link_directories($ENV{LIBOQS_LIB_DIR})

add_executable(alice_kem src/alice_kem.cpp)
target_link_libraries(alice_kem oqs)

add_executable(alice2_kem src/alice2_kem.cpp)
target_link_libraries(alice2_kem oqs)

add_executable(bob_kem src/bob_kem.cpp)
target_link_libraries(bob_kem oqs)
