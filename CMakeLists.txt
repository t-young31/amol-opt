cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)

find_package(Enzyme REQUIRED CONFIG)

message("LLVM Version: " ${Enzyme_LLVM_VERSION_MAJOR})
message("Found LLVM at: " ${Enzyme_LLVM_BINARY_DIR})

# C and C++ Compilers can only be configured before project(...)
set(CMAKE_C_COMPILER "${Enzyme_LLVM_BINARY_DIR}/bin/clang")
set(CMAKE_CXX_COMPILER "${Enzyme_LLVM_BINARY_DIR}/bin/clang++")

project(amopt)

get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("Imported targets ${importTargetsAfter}")

set(CMAKE_BUILD_TYPE Debug)

add_executable(amopt tmp.h main.cpp)
target_link_libraries(amopt PUBLIC LLDEnzymeFlags)
