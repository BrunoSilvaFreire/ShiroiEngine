set(CORE_APPLICATION
        include/application/application.h
        src/application/application.cpp
        )
set(CORE_COMMON
        include/types.h
        include/utility/event.h
        include/utility/graphic_utilities.h
        )
set(CORE_GRAPHICS
        include/graphics/buffers/opengl_buffer.h
        include/graphics/buffers/vertex_buffer.h
        include/graphics/buffers/vertex_array.h
        include/graphics/graphics_context.h
        src/graphics/graphics_context.cpp
        )
set(CORE_ALL ${CORE_APPLICATION} ${CORE_GRAPHICS} ${CORE_COMMON})
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLOG REQUIRED)
AddModule(core "${CORE_ALL}" "glfw;glew_s;glog")