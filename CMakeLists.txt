cmake_minimum_required(VERSION 3.0.0)

if (NOT DEFINED URL_BASE)
    set(URL_BASE "github.com")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB -std=c++11")

set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})

include(HunterGate)
HunterGate(
        URL "https://${URL_BASE}/FISCO-BCOS/hunter/archive/162ff7cde3d843e43afdab8fe3214275c35ef168.tar.gz"
        SHA1 "0ba8099fe89beb0d44986c750fe0d44040725d99"
        FILEPATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake"
)

project(group-signature-lib)
set(GROUP_SIG_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for group sig")

find_package(GMP REQUIRED)

include_directories(${GROUP_SIG_DIR})

include(CompilerSettings)
include(ProjectPbc)
include(ProjectPbcSig)
hunter_add_package(jsoncpp)
hunter_add_package(cryptopp)

add_subdirectory(group_sig)
