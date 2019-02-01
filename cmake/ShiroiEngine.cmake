

function(AddModule MODULE_NAME MODULE_SOURCES MODULE_DEPENDENCIES)
    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
    add_library(${MODULE_NAME} ${MODULE_SOURCES})
    list(LENGTH MODULE_SOURCES TOTAL_SOURCES)
    message("Creating module ${MODULE_NAME} (${TOTAL_SOURCES} files)")
    set(MODULE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    message(STATUS "Includes are as follow:")
    message(STATUS "Generated sources: ${CMAKE_CURRENT_SOURCE_DIR}/generated")
    message(STATUS "Include directory: ${MODULE_INCLUDE_DIR}")
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
    message(STATUS "Module ${MODULE_NAME} will be installed into '${MODULE_DESTINATION}'")
    install(
            TARGETS ${MODULE_NAME}
            DESTINATION ${MODULE_DESTINATION}
    )
    set(MODULE_RESOURCES_DESTINATION "${CMAKE_INSTALL_PREFIX}/${MODULE_NAME}/resources")
    get_target_property(MODULE_ALL_INCLUDES ${MODULE_NAME} INTERFACE_INCLUDE_DIRECTORIES)

    RecurseCollectInto(MODULE_ALL_INCLUDES ${MODULE_NAME})

    file(GLOB_RECURSE MODULE_RESOURCE_FILES ${MODULE_RESOURCES}/*)
    list(LENGTH MODULE_RESOURCE_FILES TOTAL_RESOURCES)
    if (TOTAL_RESOURCES GREATER 0)
        install(DIRECTORY ${MODULE_RESOURCES}/
                DESTINATION ${MODULE_RESOURCES_DESTINATION}
                )
        message("Found ${TOTAL_RESOURCES} resources, baked to generated directory.")
    else ()
        message(STATUS "Module ${MODULE_NAME} has no resources")
    endif ()


    # Iterate through input files
    foreach (RESOURCE ${MODULE_RESOURCE_FILES})
        file(RELATIVE_PATH RES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources ${RESOURCE})
        set(output ${CMAKE_CURRENT_SOURCE_DIR}/generated/${RES_PATH}.h)
        file(WRITE ${output} "")
        string(REGEX MATCH "([^/]+)$" filename ${RESOURCE})
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        string(TOUPPER ${filename} RESOURCE_NAME_UPPER)
        file(READ ${RESOURCE} RESOURCE_DATA HEX)
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," RESOURCE_DATA ${RESOURCE_DATA})
        configure_file(${CMAKE_HOME_DIRECTORY}/tools/embed_resource.cmake.in ${output})
        target_sources(${MODULE_NAME} PUBLIC ${output})
    endforeach ()

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