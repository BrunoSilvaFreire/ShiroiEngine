#include <application/application.h>
#include <chrono>

Application::Application(const char *appName) {
    LOG(INFO) << "Initializing application '" << appName << "'";
    applicationName = appName;
    context = new GraphicsContext(appName);
    serviceManager = new ServiceManager();
}

Application::~Application() {
    delete context;
}

const string Application::getApplicationName() const {
    return applicationName;
}

#define FAKE_DELTA_TIME 0.0166666667F

ServiceManager *Application::getServiceManager() {
    return serviceManager;
}

void Application::run() {
    LOG(INFO) << "Running application";
    auto w = context->getWindow();
    using clock = std::chrono::high_resolution_clock;
    while (!glfwGetKey(w, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(w)) {
        mainStepFunction(FAKE_DELTA_TIME);
        glfwPollEvents();
        glfwSwapBuffers(w);
    }
}

GraphicsContext *Application::getContext() const {
    return context;
}

StepFunction &Application::getMainStepFunction() {
    return mainStepFunction;
}
