set(EDITOR_ALL
        src/kuroi/main.cpp
        include/kuroi/ui/editor_service.h
        include/kuroi/ui/dock.h)
add_executable(kuroieditor "${EDITOR_ALL}")
target_link_libraries(kuroieditor ui;shiroi_scenes)
target_include_directories(kuroieditor
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )