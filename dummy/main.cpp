#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>
#include <scenes/objects/camera.h>
#include <utility/file_utility.h>
#include <scenes/objects/static_mesh.h>

int main(int count, const string *params) {
    Application app("Dummy Application");
    auto path = "../resources/core/shaders";
    ShaderProgram *program;
    try {
        program = ShaderProgram::defaultProgram(path);
    } catch (std::runtime_error &ex) {
        LOG(INFO) << "Error while loading shaders '" << ex.what() << '\'';
        return -1;
    }
    LOG(INFO) << "Successfully loaded shaders.";
    program->bind();
    Scene scene(&app);
    Camera camera(&scene);
    auto s = EmbedShapes::kQuad;
    StaticMesh cube(&scene, s);
    scene.enable();
    app.run();
    scene.disable();
    program->unbind();
}

