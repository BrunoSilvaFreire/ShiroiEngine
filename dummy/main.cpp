#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>
#include <scenes/objects/camera.h>
#include <utility/file_utility.h>
#include <scenes/objects/static_mesh.h>

#define SPEED 0.25F;

float getInput(GLFWwindow *window, int32 positive, int32 negative) {
    return (glfwGetKey(window, positive) - glfwGetKey(window, negative)) * SPEED;
}

int main(int count, const string *params) {
    try {
        Application app("Dummy Application");
        Scene scene(&app);
        Camera camera(&scene);
        auto quad = app.getServiceManager()->getService<EmbedShapes>()->getQuad();
        camera.transform.position = glm::vec3(0, 0, -10);
        StaticMesh cube(&scene, quad);
        scene.enable();
        Event<float32>::EventListener updater = [&](float32 tick) {
            auto window = app.getContext()->getWindow();
            float fwd = getInput(window, GLFW_KEY_W, GLFW_KEY_S) * tick;
            float side = getInput(window, GLFW_KEY_D, GLFW_KEY_A) * tick;
            float upDown = getInput(window, GLFW_KEY_Q, GLFW_KEY_E) * tick;
            camera.transform.position += glm::vec3(fwd, upDown, side);
        };
        app.getMainStepFunction().getEarlyStep() += &updater;
        app.run();
        scene.disable();
    } catch (std::runtime_error &ex) {
        LOG(INFO) << "Error while loading shaders '" << ex.what() << '\'';
        return -1;
    }

}

