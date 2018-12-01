#include <graphics/graphics_context.h>
#include <glog/logging.h>

void errorCB(int a, const char *desc) {
    LOG(ERROR) << "GLFW error #" << a << ": " << desc;
}

GraphicsContext::GraphicsContext(const string windowTitle, uint32 width, uint32 height) {

    LOG(INFO) << "Initializing GLFW";
    auto glfwInitCode = glfwInit();
    if (glfwInitCode != GLFW_TRUE) {
        LOG(ERROR) << "An error occoured while initializing GLFW (" << glfwInitCode << ")";
        throw std::runtime_error("Error while initializing GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(errorCB);
    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Couldn't create GLFW window");
    }
    glfwMakeContextCurrent(window);
    LOG(INFO) << "GLFW OK";
    LOG(INFO) << "Initializing GLEW";
    auto glewInitCode = glewInit();
    if (glewInitCode != GLEW_OK) {
        LOG(ERROR) << "An error occoured while initializing GLEW (" << glewInitCode << ") '"
                   << glewGetErrorString(glewInitCode) << "'";
        throw std::runtime_error("Error while initializing GLEW");
    }
    glFrontFace(GL_CW);

    LOG(INFO) << "GLEW OK";
    LOG(INFO) << "OpenGL '" << glGetString(GL_VERSION) << "' succesfully initialized (GLFW: " << glfwGetVersionString()
              << ")";
}

GraphicsContext::~GraphicsContext() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

GLFWwindow *GraphicsContext::getWindow() {
    return window;
}