#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>
#include <scenes/objects/camera.h>
#include <utility/file_utility.h>
#include <scenes/objects/static_mesh.h>

int main() {
    Application app("Dummy Application");
    auto path = getExecutableDirectory();
    LOG(INFO) << "Executing @ '" << path << '\'';
    path += "/../resources/core/shaders";
    ShaderProgram *program;
    try {
        program = ShaderProgram::defaultProgram(path.c_str());
    } catch (std::runtime_error &ex) {
        return -1;
    }
    LOG(INFO) << "Successfully loaded shaders.";
    program->bind();
    Scene scene(&app);
    Camera camera(&scene);
    StaticMesh cube(&scene, EmbedShapes::kCube);
    scene.enable();
    app.run();
    scene.disable();
    program->unbind();
}

