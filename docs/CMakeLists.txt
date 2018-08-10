# Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # input and ouput files
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(documentation
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    ) 
else(DOXYGEN_FOUND)
    message(WARNING "Doxygen doit être installé pour pouvoir générer la documentation")
endif(DOXYGEN_FOUND)