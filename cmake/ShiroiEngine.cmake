function(AddModule MODULE_NAME MODULE_SOURCES MODULE_DEPENDENCIES)
    add_library(${MODULE_NAME} ${MODULE_SOURCES})
    message("----- Creating module ${MODULE_NAME}... -----")
    #message("Using include directory '${CMAKE_CURRENT_SOURCE_DIR}/include'")
    set(MODULE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    message("Includes are as follow:")
    message("Generated sources: ${CMAKE_CURRENT_SOURCE_DIR}/generated")
    message("Include directory: ${MODULE_INCLUDE_DIR}")
    target_include_directories(${MODULE_NAME}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/generated>
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
    get_target_property(MODULE_ALL_INCLUDES ${MODULE_NAME} INTERFACE_INCLUDE_DIRECTORIES)

    RecurseCollectInto(MODULE_ALL_INCLUDES ${MODULE_NAME})
    install(DIRECTORY ${MODULE_RESOURCES}/
            DESTINATION ${MODULE_RESOURCES_DESTINATION}
            )

    file(GLOB_RECURSE MODULE_ALL_FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    add_custom_target(
            ${MODULE_NAME}_run_jen
            DEPENDS ${MODULE_NAME} jen
            COMMAND
            $<TARGET_FILE:jen> --fileList "${MODULE_ALL_FILES}" --outputPath "${CMAKE_CURRENT_SOURCE_DIR}/generated" --includePath "${MODULE_ALL_INCLUDES}"
    )
    message("")
endfunction()
macro(RecurseCollectInto DESTINATION TARGET)
    get_target_property(TEMP_DEPENDENCIES ${TARGET} INTERFACE_LINK_LIBRARIES)
    if (NOT "${TEMP_DEPENDENCIES}" STREQUAL TEMP_DEPENDENCIES-NOTFOUND)
        foreach (dep ${TEMP_DEPENDENCIES})
            if (TARGET ${dep})
                get_target_property(TEMP_INCLUDES ${dep} INTERFACE_INCLUDE_DIRECTORIES)
                if (NOT "${TEMP_INCLUDES}" STREQUAL "")
                    set(${DESTINATION} "${TEMP_INCLUDES};${${DESTINATION}}")
                    RecurseCollectInto(${DESTINATION} ${dep})
                endif ()
            endif ()
        endforeach ()
    endif ()

endmacro()