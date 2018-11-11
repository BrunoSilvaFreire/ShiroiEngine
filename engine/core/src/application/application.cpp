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

const string Application::getApplicationName() const {
    return applicationName;
}

#define FAKE_DELTA_TIME 0.0166666667F

void Application::run() {
    auto w = context->getWindow();
    using clock = std::chrono::high_resolution_clock;
    while (!glfwGetKey(w, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(w)) {
        earlyUpdateEvent(FAKE_DELTA_TIME);
        lateUpdateEvent(FAKE_DELTA_TIME);
        glfwPollEvents();
        glfwSwapBuffers(w);
    }
}

GraphicsContext *Application::getContext() const {
    return context;
}

Event<float32> &Application::getEarlyUpdateEvent() {
    return earlyUpdateEvent;
}

Event<float32> &Application::getLateUpdateEvent() {
    return lateUpdateEvent;
}
