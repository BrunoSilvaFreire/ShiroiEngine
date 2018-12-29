add_executable(dummy main.cpp)
target_link_libraries(dummy core shiroi_scenes)
install(TARGETS dummy
        DESTINATION ${CMAKE_INSTALL_PREFIX}/dummy
        )