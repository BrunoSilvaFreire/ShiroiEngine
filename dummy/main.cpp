#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>
#include <scenes/objects/camera.h>
#include <utility/file_utility.h>
#include <scenes/objects/static_mesh.h>
#include <maths/angles.h>
#include <serialization/serialized_object.h>

#define SPEED 0.25F
#define ROT_SPEED 1.0F

float getInput(GLFWwindow *window, int32 positive, int32 negative) {
    return (glfwGetKey(window, positive) - glfwGetKey(window, negative)) * SPEED;
}

int main(int count, const c_string *params) {
    try {
        Application app("Dummy Application");
        Scene scene(&app);
        Camera camera(&scene);
        auto quad = app.getServiceManager()->getService<EmbedShapes>()->getQuad();
        camera.transform.position = glm::vec3(0, 0, -10);
        StaticMesh cube(&scene, quad);
        StaticMesh floor(&scene, quad);
        floor.transform.position = glm::vec3(0, -5, 0);
        floor.transform.rotation = glm::quat(glm::vec3(0, 90, 0));
        floor.transform.scale = glm::vec3(10, 10, 1);
        scene.enable();
        float64 lastMouseX, lastMouseY;
        glfwGetCursorPos(app.getContext()->getWindow(), &lastMouseX, &lastMouseY);
        Event<float32>::EventListener updater = [&](float32 tick) {
            auto window = app.getContext()->getWindow();
            float fwd = getInput(window, GLFW_KEY_W, GLFW_KEY_S) * tick;
            float side = getInput(window, GLFW_KEY_D, GLFW_KEY_A) * tick;
            float upDown = getInput(window, GLFW_KEY_Q, GLFW_KEY_E) * tick;
            auto t = camera.transform;
            auto fwdV = t.getForward();
            fwdV *= fwd;
            auto sideV = t.getRight();
            sideV *= side;
            auto verticalV = t.getUp();
            verticalV *= upDown;
            fwdV += verticalV;
            fwdV += sideV;
            // Normalize
            float s = fwdV.length();
            t.position += fwdV;
            float64 newMouseX, newMouseY;
            glfwGetCursorPos(app.getContext()->getWindow(), &newMouseX, &newMouseY);
            auto dX = newMouseX - lastMouseX;
            auto dY = newMouseY - lastMouseY;
            lastMouseX = newMouseX;
            lastMouseY = newMouseY;
            auto rot = glm::eulerAngles(t.rotation);
            rot.y += dX * (ROT_SPEED * tick);
            rot.x -= dY * (ROT_SPEED * tick);
            t.rotation = glm::quat(rot);
            camera.transform = t;
        };
        app.getMainStepFunction().getEarlyStep() += &updater;
        app.run();
        scene.disable();
    } catch (std::runtime_error &ex) {
        LOG(INFO) << "Error while loading shaders '" << ex.what() << '\'';
        return -1;
    }

}

