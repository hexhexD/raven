cmake_minimum_required(VERSION 3.2)

project(Raven)
set(CMAKE_CXX_STANDARD 20)

# Ninja color output
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()

add_executable(raven src/raven.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(raven PRIVATE Threads::Threads)

target_include_directories(raven PUBLIC third-party/asio)
