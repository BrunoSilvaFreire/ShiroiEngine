message("Hello 2")

set(SCENES_SOURCES
        include/scenes/scene.h
        include/scenes/objects/camera.h
        include/scenes/objects/static_mesh.h
        src/scenes/objects/static_mesh.cpp
        src/scenes/objects/camera.cpp
        src/scenes/scene.cpp)
AddModule(
        shiroi_scenes
        "${SCENES_SOURCES}"
        "core"
)

