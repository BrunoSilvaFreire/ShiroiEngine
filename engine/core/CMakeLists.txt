set(CORE_APPLICATION
        include/application/application.h
        src/application/application.cpp
        )
set(CORE_COMMON
        include/types.h
        include/utility/event.h
        include/utility/graphic_utilities.h
        include/utility/string_utility.h
        src/utility/string_utility.cpp
        src/graphics/utility/graphic_utilities.cpp
        include/services/builtin/embed_shapes.h
        src/services/builtin/embed_shapes.cpp
        include/utility/step_function.h
        src/utility/step_function.cpp
        include/utility/collection_utilities.h
        )

set(CORE_MATHS
        include/maths/angles.h
        )
set(CORE_SERIALIZATION
        include/serialization/serialized_object.h
        include/serialization/annotation_macros.h
        )
set(CORE_DEBUG
        include/utility/debug_utility.h)
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

set(CORE_SERVICES
        include/services/service.h
        src/services/service.cpp
        include/services/service_manager.h
        src/services/service_manager.cpp
        )
set(CORE_GRAPHICS
        include/graphics/graphics_context.h
        src/graphics/graphics_context.cpp
        include/graphics/rendering.h
        src/graphics/rendering.cpp
        include/graphics/mesh.h
        src/graphics/mesh.cpp
        include/graphics/material.h
        src/graphics/material.cpp
        ${CORE_BUFFERS}
        ${CORE_SHADERS}
        )
set(CORE_ALL ${CORE_APPLICATION} ${CORE_GRAPHICS} ${CORE_COMMON} ${CORE_DEBUG} ${CORE_MATHS})
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLOG REQUIRED)
find_package(TinyObjLoader REQUIRED)
AddModule(core "${CORE_ALL}" "glfw;glew_s;glog;glm;tinyobjloader")