# Set files in sub directory like set_subdir_sources( a.cpp b.cpp c.cpp )
macro( set_subdir_sources )
    foreach( SOURCE_FILE ${ARGN} )
        set( SRC_LIST ${SRC_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE} )
    endforeach()
    set( SRC_LIST ${SRC_LIST} PARENT_SCOPE )
endmacro()
