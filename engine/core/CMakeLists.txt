set(CORE_APPLICATION
        include/application/application.h
        src/application/application.cpp
        )
set(CORE_COMMON
        include/types.h
        include/utility/event.h
        include/utility/graphic_utilities.h
        src/graphics/utility/graphic_utilities.cpp
        )

set(CORE_SCENES
        include/scenes/scene.h
        include/scenes/objects/camera.h
        src/scenes/objects/camera.cpp
        )
set(CORE_BUFFERS
        include/graphics/buffers/opengl_buffer.h
        include/graphics/buffers/vertex_buffer.h
        include/graphics/buffers/vertex_array.h
        src/graphics/buffers/verter_array.cpp
        src/graphics/buffers/vertex_buffer.cpp
        )
set(CORE_SHADERS
        include/graphics/shaders/shader_program.h
        )

set(CORE_GRAPHICS
        include/graphics/graphics_context.h
        src/graphics/graphics_context.cpp
        include/graphics/rendering.h
        src/graphics/rendering.cpp
        ${CORE_BUFFERS}
        ${CORE_SHADERS}
        )
set(CORE_ALL ${CORE_APPLICATION} ${CORE_GRAPHICS} ${CORE_COMMON} ${CORE_SCENES})
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLOG REQUIRED)
message("include dir is '${Boost_INCLUDE_DIRS}'")
AddModule(core "${CORE_ALL}" "glfw;glew_s;glog;glm;")