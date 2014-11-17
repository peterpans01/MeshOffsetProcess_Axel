project(mypkg_src)

set(PKG_NAME MYPKG)
set(LIB_NAME mypkg)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})
set(${PROJECT_NAME}_HEADERS
   my_class.h
)
set(${PROJECT_NAME}_SOURCES
  ${PROJECT_SOURCE_DIR}/my_class.cpp
)

IF(BUILD_FOR_RELEASE)
    add_library(${LIB_NAME} STATIC ${${PROJECT_NAME}_SOURCES})
    link_libraries(${LIB_NAME} )
    install(TARGETS ${LIB_NAME} DESTINATION lib )
ELSE(BUILD_FOR_RELEASE)
    IF(STATIC)
        IF(SHARED)
            add_library(${LIB_NAME}_static STATIC ${${PROJECT_NAME}_SOURCES})
            link_libraries(${LIB_NAME}_static )
            install(TARGETS ${LIB_NAME}_static DESTINATION lib )
        ELSE(SHARED)
            add_library(${LIB_NAME} STATIC ${${PROJECT_NAME}_SOURCES})
            link_libraries(${LIB_NAME} )
            install(TARGETS ${LIB_NAME} DESTINATION lib )
        ENDIF(SHARED)
    ENDIF(STATIC)

    IF(SHARED)
        add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCES})
        link_libraries(${LIB_NAME} )
        install(TARGETS ${LIB_NAME} DESTINATION lib )
    ENDIF(SHARED)
ENDIF(BUILD_FOR_RELEASE)


####################################################################
## Installation
####################################################################
install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${LIB_NAME}
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib)

