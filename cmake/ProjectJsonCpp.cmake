include(ExternalProject)

if (NOT JSONCPP_ROOT)
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
        set(JSONCPP_CMAKE_COMMAND emcmake cmake)
    else()
        set(JSONCPP_CMAKE_COMMAND ${CMAKE_COMMAND})
    endif()

    ExternalProject_Add(jsoncpp
        PREFIX ${CMAKE_SOURCE_DIR}/deps
        DOWNLOAD_NAME jsoncpp-1.7.7.tar.gz
        DOWNLOAD_NO_PROGRESS 1
        URL https://github.com/open-source-parsers/jsoncpp/archive/1.7.7.tar.gz
        URL_HASH SHA256=087640ebcf7fbcfe8e2717a0b9528fff89c52fcf69fa2a18cc2b538008098f97
        CMAKE_COMMAND ${JSONCPP_CMAKE_COMMAND}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
                -DJSONCPP_WITH_TESTS=Off
                -DJSONCPP_WITH_PKGCONFIG_SUPPORT=Off
                    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
        BUILD_BYPRODUCTS <INSTALL_DIR>/lib/libjsoncpp.a
    )

    # Create jsoncpp imported library
    ExternalProject_Get_Property(jsoncpp INSTALL_DIR)
    set(JSONCPP_ROOT ${INSTALL_DIR}/include)
    unset(INSTALL_DIR)
endif()
add_library(JsonCpp STATIC IMPORTED)
set(JSONCPP_LIBRARY ${JSONCPP_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}jsoncpp${CMAKE_STATIC_LIBRARY_SUFFIX})
set(JSONCPP_INCLUDE_DIR ${JSONCPP_ROOT}/include)
file(MAKE_DIRECTORY ${JSONCPP_INCLUDE_DIR})  # Must exist.
set_property(TARGET JsonCpp PROPERTY IMPORTED_LOCATION ${JSONCPP_LIBRARY})
set_property(TARGET JsonCpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${JSONCPP_INCLUDE_DIR})
add_dependencies(JsonCpp jsoncpp)
