set (PKG_HTML_DIR  html)

######################################################################
# Build documentation 
######################################################################
message("   with html documentation in ${PKG_HTML_DIR}")

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/doxygen/doxyfile-cmake.in"
		"${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/doxyfile" )
add_definitions (-DHAVE_CONFIG_H)

add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/.doxygen
                    COMMAND doxygen ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/doxyfile 
                    DEPENDS ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/.setup
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/.setup
                    COMMAND  mkdir -p ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR} && echo >${PKG_HTML_DIR}/.setup
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_target (${PROJECT_NAME}_html ALL
                   DEPENDS
                     ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/.setup
                     ${CMAKE_BINARY_DIR}/${PKG_HTML_DIR}/.doxygen
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMENT  "html documentation")

add_custom_target (clean_${PROJECT_NAME}_html
                   COMMAND rm  -f ${PKG_HTML_DIR}/.doxygen ${PKG_HTML_DIR}/.setup ${PKG_HTML_DIR}/*.html 
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMENT "clean html setup and dox files")

add_custom_target (clean_${PROJECT_NAME}_doxygen
                   COMMAND rm ${PKG_HTML_DIR}/.doxygen  
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMENT "clean doxygen setup")
