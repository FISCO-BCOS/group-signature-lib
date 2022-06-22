include(ExternalProject)
set(PBC_SIG_PATCH cp ${CMAKE_SOURCE_DIR}/patch/pbc_sig.patch ${CMAKE_SOURCE_DIR}/deps/src/pbc_sig && patch -f -p1 < ${CMAKE_SOURCE_DIR}/deps/src/pbc_sig/pbc_sig.patch && cp ${CMAKE_CURRENT_LIST_DIR}/config.guess <SOURCE_DIR>)

ExternalProject_Add(pbc_sig
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NAME pbc_sig-0.0.8.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    URL https://osp-1257653870.cos.ap-guangzhou.myqcloud.com/FISCO-BCOS/deps/pbc/pbc_sig-0.0.8.tar.gz
        https://crypto.stanford.edu/pbc/sig/files/pbc_sig-0.0.8.tar.gz
    URL_HASH SHA256=7a343bf342e709ea41beb7090c78078a9e57b833454c695f7bcad2475de9c4bb
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ${PBC_SIG_PATCH}
    CMAKE_COMMAND ${CMAKE_COMMAND}
    CMAKE_ARGS --debug-output
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    INSTALL_COMMAND bash -c "/bin/cp -f libpbc_sig.a ${CMAKE_SOURCE_DIR}/deps/lib/libpbc_sig.a && /bin/cp -f include/* ${CMAKE_SOURCE_DIR}/deps/include/pbc/"
)

add_dependencies(pbc_sig pbc)
ExternalProject_Get_Property(pbc_sig SOURCE_DIR)
ExternalProject_Get_Property(pbc_sig INSTALL_DIR)

add_library(Pbc_sig STATIC IMPORTED)
set(PBC_SIG_INCLUDE_DIR ${INSTALL_DIR}/include)
set(PBC_SIG_LIBRARY ${INSTALL_DIR}/lib/libpbc_sig.a)
file(MAKE_DIRECTORY ${PBC_SIG_INCLUDE_DIR})  # Must exist.
file(MAKE_DIRECTORY ${INSTALL_DIR}/lib)  # Must exist.
set_property(TARGET Pbc_sig PROPERTY IMPORTED_LOCATION ${PBC_SIG_LIBRARY})
set_property(TARGET Pbc_sig PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PBC_SIG_INCLUDE_DIR})
add_dependencies(Pbc_sig pbc_sig)
unset(INSTALL_DIR)
