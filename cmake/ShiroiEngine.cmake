function(AddModule MODULE_NAME MODULE_SOURCES MODULE_DEPENDENCIES)
    add_library(${MODULE_NAME} ${MODULE_SOURCES})
    message("Creating module ${MODULE_NAME}...")
    #message("Using include directory '${CMAKE_CURRENT_SOURCE_DIR}/include'")
    set(MODULE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${MODULE_NAME}
            PUBLIC
            $<BUILD_INTERFACE:${MODULE_INCLUDE_DIR}>
            $<INSTALL_INTERFACE:include>
            )
    set_target_properties(${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
    foreach (dependency ${MODULE_DEPENDENCIES})
        target_link_libraries(${MODULE_NAME} ${dependency})
    endforeach ()
    set(MODULE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    set(MODULE_DESTINATION "${CMAKE_INSTALL_PREFIX}/modules/${MODULE_NAME}")
    message("Module ${MODULE_NAME} will be installed into '${MODULE_DESTINATION}'")
    install(
            TARGETS ${MODULE_NAME}
            DESTINATION ${MODULE_DESTINATION}
    )
    set(MODULE_RESOURCES_DESTINATION "${CMAKE_INSTALL_PREFIX}/resources/${MODULE_NAME}")
    message("Resources of ${MODULE_NAME} will be installed into '${MODULE_RESOURCES_DESTINATION}'")
    install(DIRECTORY ${MODULE_RESOURCES}/
            DESTINATION ${MODULE_RESOURCES_DESTINATION}
            )
endfunction()