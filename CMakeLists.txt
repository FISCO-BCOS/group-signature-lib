cmake_minimum_required(VERSION 3.0.0)

if (NOT DEFINED URL_BASE)
    set(URL_BASE "github.com")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB -std=c++11")

set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})

# vcpkg init
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    find_package(Git REQUIRED)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- vcpkg WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(group-signature-lib)
set(GROUP_SIG_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for group sig")

find_package(GMP REQUIRED)
include_directories(${GROUP_SIG_DIR})

include(CompilerSettings)
include(ProjectPbc)
include(ProjectPbcSig)
#hunter_add_package(jsoncpp)
#hunter_add_package(cryptopp)

add_subdirectory(group_sig)
