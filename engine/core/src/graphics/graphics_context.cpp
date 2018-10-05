#include <graphics/graphics_context.h>
#include <glog/logging.h>


GraphicsContext::GraphicsContext(const string windowTitle, uint32 width, uint32 height) {

    LOG(INFO) << "Initializing GLFW";
    auto glfwInitCode = glfwInit();
    if (glfwInitCode != GLFW_TRUE) {
        LOG(ERROR) << "An error occoured while initializing GLFW (" << glfwInitCode << ")";
        throw std::runtime_error("Error while initializing GLFW");
    }
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Couldn't create GLFW window");
    }
    glfwMakeContextCurrent(window);
    LOG(INFO) << "Initializing GLEW";
    auto glewInitCode = glewInit();

    if (glewInitCode != GLEW_OK) {
        LOG(ERROR) << "An error occoured while initializing GLEW (" << glewInitCode << ") '"
                   << glewGetErrorString(glewInitCode) << "'";
        throw std::runtime_error("Error while initializing GLEW");
    }

    LOG(INFO) << "OpenGL '" << glGetString(GL_VERSION) << "' succesfully initialized (GLFW: " << glfwGetVersionString()
              << ")";
}

GraphicsContext::~GraphicsContext() {
    if (window != nullptr) {
        LOG(INFO) << "Destroying GLFW window";
        glfwDestroyWindow(window);
    }
    LOG(INFO) << "Termination GLFW";
    glfwTerminate();
}

GLFWwindow *GraphicsContext::getWindow() {
    return window;
}
