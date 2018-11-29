#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>
#include <scenes/objects/camera.h>
#include <utility/file_utility.h>
#include <scenes/objects/static_mesh.h>

int main(int count, const string *params) {
    try {
        Application app("Dummy Application");
        Scene scene(&app);
        Camera camera(&scene);
        auto quad = app.getServiceManager()->getService<EmbedShapes>()->getQuad();
        StaticMesh cube(&scene, quad);
        scene.enable();
        app.run();
        scene.disable();
    } catch (std::runtime_error &ex) {
        LOG(INFO) << "Error while loading shaders '" << ex.what() << '\'';
        return -1;
    }

}

