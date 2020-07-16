include(ExternalProject)
include(GNUInstallDirs)

if (NOT CRYPTOPP_ROOT)
    set(INSTALL_LIB cp -f ../cryptopp-build/libcryptopp.a ${CMAKE_SOURCE_DIR}/deps/lib)

    ExternalProject_Add(cryptopp
        PREFIX ${CMAKE_SOURCE_DIR}/deps
        # This points to unreleased version 5.6.5+ but contains very small
        # warning fix:
        # https://github.com/weidai11/cryptopp/commit/903b8feaa70199eb39a313b32a71268745ddb600
        DOWNLOAD_NAME cryptopp_bccc6443.tar.gz
        DOWNLOAD_NO_PROGRESS 1
        URL https://github.com/weidai11/cryptopp/archive/bccc6443c4d4d611066c2de4c17109380cf97704.tar.gz
        URL_HASH SHA256=f1fddacadd2a0873f795d5614a85fecd5b6ff1d1c6e21dedc251703c54ce63aa
        PATCH_COMMAND ${CMAKE_COMMAND} -E remove
            3way.cpp
            adler32.cpp
            arc4.cpp
            authenc.cpp
            base32.cpp
            base64.cpp
            bench1.cpp
            bench2.cpp
            bfinit.cpp
            blake2.cpp
            blowfish.cpp
            blumshub.cpp
            camellia.cpp
            cast.cpp
            casts.cpp
            cbcmac.cpp
            ccm.cpp
            chacha.cpp
            channels.cpp
            cmac.cpp
            crc.cpp
            datatest.cpp
            default.cpp
            des.cpp
            dessp.cpp
            dh2.cpp
            dh.cpp
            dlltest.cpp
            eax.cpp
            elgamal.cpp
            emsa2.cpp
            esign.cpp
            files.cpp
            fipsalgt.cpp
            fipstest.cpp
            gcm.cpp
            gf2_32.cpp
            gf256.cpp
            gost.cpp
            gzip.cpp
            ida.cpp
            idea.cpp
            luc.cpp
            mars.cpp
            marss.cpp
            md2.cpp
            md4.cpp
            md5.cpp
            mqv.cpp
            network.cpp
            panama.cpp
            pch.cpp
            pkcspad.cpp
            poly1305.cpp
            pssr.cpp
            rabin.cpp
            rc2.cpp
            rc5.cpp
            rc6.cpp
            rdrand.cpp
            regtest.cpp
            ripemd.cpp
            rsa.cpp
            rw.cpp
            safer.cpp
            salsa.cpp
            seal.cpp
            seed.cpp
            serpent.cpp
            sha3.cpp
            shacal2.cpp
            sharkbox.cpp
            shark.cpp
            simple.cpp
            skipjack.cpp
            socketft.cpp
            sosemanuk.cpp
            square.cpp
            squaretb.cpp
            tea.cpp
            test.cpp
            tftables.cpp
            tiger.cpp
            tigertab.cpp
            trdlocal.cpp
            ttmac.cpp
            twofish.cpp
            validat0.cpp
            validat1.cpp
            validat2.cpp
            validat3.cpp
            vmac.cpp
            wait.cpp
            wake.cpp
            whrlpool.cpp
            xtr.cpp
            xtrcrypt.cpp
            zdeflate.cpp
            zinflate.cpp
            zlib.cpp
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
            -DCMAKE_BUILD_TYPE=Release
            # Build static lib but suitable to be included in a shared lib.
            -DCMAKE_POSITION_INDEPENDENT_CODE=${BUILD_SHARED_LIBS}
            -DBUILD_SHARED=Off
            -DBUILD_TESTING=Off
            -DCMAKE_C_FLAGS=${MARCH_TYPE}
            -DCMAKE_CXX_FLAGS=${MARCH_TYPE}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        COMMAND ${INSTALL_LIB}
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
    )
    ExternalProject_Get_Property(cryptopp INSTALL_DIR)
    set(CRYPTOPP_ROOT ${INSTALL_DIR}/include)
    unset(INSTALL_DIR)
endif()

add_library(Cryptopp STATIC IMPORTED)
set(CRYPTOPP_LIBRARY ${CRYPTOPP_ROOT}/${CMAKE_INSTALL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}cryptopp${CMAKE_STATIC_LIBRARY_SUFFIX})
set(CRYPTOPP_INCLUDE_DIR ${CRYPTOPP_ROOT}/include)
file(MAKE_DIRECTORY ${CRYPTOPP_INCLUDE_DIR})  # Must exist.
set_property(TARGET Cryptopp PROPERTY IMPORTED_LOCATION ${CRYPTOPP_LIBRARY})
set_property(TARGET Cryptopp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CRYPTOPP_INCLUDE_DIR})
add_dependencies(Cryptopp cryptopp)
