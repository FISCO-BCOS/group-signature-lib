include(ExternalProject)

if(GMP_INCLUDE_DIR)
    set(CPPFLAG_CMD "CPPFLAGS=-I${GMP_INCLUDE_DIR}")
    message(STATUS "GMP_INCLUDE_DIR: ${GMP_INCLUDE_DIR}")
endif()

if(GMP_LIB_DIR)
    set(LDFLAGS_CMD "LDFLAGS=-L${GMP_LIB_DIR}")
    message(STATUS "GMP_LIB_DIR: ${GMP_LIB_DIR}")
endif()

set(PBC_PBCSTRAP_COMMAND ./configure ${CPPFLAG_CMD} ${LDFLAGS_CMD} --prefix=${CMAKE_SOURCE_DIR}/deps)

ExternalProject_Add(pbc
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NO_PROGRESS 1
    URL https://osp-1257653870.cos.ap-guangzhou.myqcloud.com/FISCO-BCOS/deps/pbc/pbc-0.5.14.tar.gz
        https://crypto.stanford.edu/pbc/files/pbc-0.5.14.tar.gz
    URL_HASH SHA256=772527404117587560080241cedaf441e5cac3269009cdde4c588a1dce4c23d2
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}/config.guess <SOURCE_DIR>
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${PBC_PBCSTRAP_COMMAND}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)
ExternalProject_Get_Property(pbc SOURCE_DIR)
find_package(GMP REQUIRED)
ExternalProject_Get_Property(pbc INSTALL_DIR)
add_library(Pbc STATIC IMPORTED)
set(PBC_INCLUDE_DIR ${INSTALL_DIR}/include)
set(PBC_LIBRARY ${INSTALL_DIR}/lib/libpbc.a)

file(MAKE_DIRECTORY ${PBC_INCLUDE_DIR})  # Must exist.
file(MAKE_DIRECTORY ${INSTALL_DIR}/lib)  # Must exist.
set_property(TARGET Pbc PROPERTY IMPORTED_LOCATION ${PBC_LIBRARY})
set_property(TARGET Pbc PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PBC_INCLUDE_DIR})
add_dependencies(Pbc pbc)
unset(INSTALL_DIR)
