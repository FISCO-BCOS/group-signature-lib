cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB -std=c++11")

set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})
set(GROUP_SIG_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for group sig")

find_package(GMP REQUIRED)

include_directories(${GROUP_SIG_DIR})

include(CompilerSettings)
include(ProjectCryptopp)
include(ProjectPbc)
include(ProjectPbcSig)
include(ProjectJsonCpp)

add_subdirectory(group_sig)
