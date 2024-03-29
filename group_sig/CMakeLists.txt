file(GLOB ALGORITHM_BBS04_SRC "algorithm/bbs04/*.cpp")
file(GLOB ALGORITHM_BBS04_HEADERS "algorithm/bbs04/*.h")

file(GLOB ALGORITHM_RING_SIG_SRC "algorithm/ring-sig/*.cpp")
file(GLOB ALGORITHM_RING_SIG_HEADERS "algorithm/ring-sig/*.h")

file(GLOB ALGORITHM_SRC "algorithm/*.cpp")
file(GLOB ALGORITHM_HEADERS "algorithm/*.h")

file(GLOB DEVCORE_SRC "devcore/*.cpp")
file(GLOB DEVCORE_HEADERS "devcore/*.h")

list(APPEND SRC_LIST ${ALGORITHM_BBS04_SRC})
list(APPEND HEADERS ${ALGORITHM_BBS04_HEADERS})

list(APPEND SRC_LIST ${ALGORITHM_RING_SIG_SRC})
list(APPEND HEADERS ${ALGORITHM_RING_SIG_HEADERS})

list(APPEND SRC_LIST ${ALGORITHM_SRC})
list(APPEND HEADERS ${ALGORITHM_HEADERS})

list(APPEND SRC_LIST ${DEVCORE_SRC})
list(APPEND HEADERS ${DEVCORE_HEADERS})

find_package(GMP REQUIRED)

add_library(group_sig STATIC ${SRC_LIST} ${HEADERS})

find_package(jsoncpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(group_sig PUBLIC Pbc_sig Pbc Gmp cryptopp-static jsoncpp_lib_static)

INSTALL(TARGETS group_sig RUNTIME DESTINATION bin/ ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
INSTALL(FILES ${ALGORITHM_BBS04_HEADERS} DESTINATION include/group_sig/algorithm/bbs04/) 
INSTALL(FILES ${ALGORITHM_RING_SIG_HEADERS} DESTINATION include/group_sig/algorithm/ring-sig/) 
INSTALL(FILES ${ALGORITHM_HEADERS} DESTINATION include/group_sig/algorithm/) 
INSTALL(FILES ${DEVCORE_HEADERS} DESTINATION include/group_sig/devcore/) 
