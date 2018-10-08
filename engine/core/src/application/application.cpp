#include <application/application.h>
#include <chrono>


Application::Application(const char *appName) {
    LOG(INFO) << "Initializing application";
    applicationName = appName;
    context = new GraphicsContext(appName);
}

Application::~Application() {
    delete context;
}

Event<float32> &Application::getTickEvent() {
    return tickEvent;
}

const string Application::getApplicationName() const {
    return applicationName;
}

void Application::run() {
    auto w = context->getWindow();
    using clock = std::chrono::high_resolution_clock;
    while (!glfwGetKey(w, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(w)) {
        tickEvent(0.0166666667F);
        renderEvent(context);
        glfwPollEvents();
        glfwSwapBuffers(w);
    }
}

GraphicsContext *Application::getContext() const {
    return context;
}

Event<GraphicsContext *> &Application::getRenderEvent() {
    return renderEvent;
}
