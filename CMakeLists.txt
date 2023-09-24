cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)

find_package(Enzyme REQUIRED CONFIG)

message("LLVM Version: " ${Enzyme_LLVM_VERSION_MAJOR})
message("Found LLVM at: " ${Enzyme_LLVM_BINARY_DIR})

# C and C++ Compilers can only be configured before project(...)
set(CMAKE_C_COMPILER "${Enzyme_LLVM_BINARY_DIR}/bin/clang")
set(CMAKE_CXX_COMPILER "${Enzyme_LLVM_BINARY_DIR}/bin/clang++")

project(amopt)

get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
message("Imported targets ${importTargetsAfter}")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3 -ffast-math")

include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB amopt_SRC CONFIGURE_DEPENDS
     "src/*.cpp"
)

# Default the build type to Release
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

add_executable(amopt ${amopt_SRC})
target_link_libraries(amopt PUBLIC LLDEnzymeFlags)

message("-- Debug init flags: ${CMAKE_BUILD_TYPE}")
message("-- Release init flags: ${CMAKE_CXX_FLAGS_RELEASE_INIT}")
