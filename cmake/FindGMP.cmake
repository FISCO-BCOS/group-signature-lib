if( TARGET Gmp )
    return()
endif()

unset( GMP_LIBRARIES CACHE )
unset( GMP_LIBRARIES )
unset( GMP_INCLUDE_DIR CACHE )
unset( GMP_INCLUDE_DIR )
unset( GMP_LIB_DIR CACHE )
unset( GMP_LIB_DIR )

message( STATUS "Looking for GMP" )
   find_library( GMP_LIBRARIES NAMES "libgmp.a" )
   find_path( GMP_INCLUDE_DIR "gmp.h" )
if( NOT GMP_LIBRARIES )
   message( FATAL_ERROR "GMP library not found" )
endif()
if( NOT GMP_INCLUDE_DIR )
   message( FATAL_ERROR "GMP includes not found" )
endif()
message(STATUS "GMP:${GMP_LIBRARIES}")

get_filename_component( GMP_LIB_DIR "${GMP_LIBRARIES}" DIRECTORY )

add_library( Gmp UNKNOWN IMPORTED )
set_property( TARGET Gmp PROPERTY IMPORTED_LOCATION "${GMP_LIBRARIES}" )
set_property( TARGET Gmp PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}" )

mark_as_advanced(
    GMP_LIBRARIES
    GMP_INCLUDE_DIR
    GMP_LIB_DIR
    )
