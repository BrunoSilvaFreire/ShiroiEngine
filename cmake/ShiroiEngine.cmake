# Get all propreties that cmake supports
execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)

# Convert command output into a CMake list
STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

function(print_properties)
    message("CMAKE_PROPERTY_LIST = ${CMAKE_PROPERTY_LIST}")
endfunction(print_properties)

function(print_target_properties tgt)
    if (NOT TARGET ${tgt})
        message("There is no target named '${tgt}'")
        return()
    endif ()

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
        if (prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
            continue()
        endif ()
        # message ("Checking ${prop}")
        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
        if (propval)
            get_target_property(propval ${tgt} ${prop})
            message("${tgt} ${prop} = ${propval}")
        endif ()
    endforeach (prop)
endfunction(print_target_properties)

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
        message("Added library '${dependency}'")
        target_link_libraries(${MODULE_NAME} ${dependency})
    endforeach ()
    set(MODULE_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    install(
            TARGETS ${MODULE_NAME}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/modules/${MODULE_NAME}
    )
    #[[install(DIRECTORY ${MODULE_INCLUDE_DIR}/
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${MODULE_NAME})]]
    install(DIRECTORY ${MODULE_RESOURCES}/
            DESTINATION ${CMAKE_INSTALL_PREFIX}/resources/${MODULE_NAME}
            )
endfunction()