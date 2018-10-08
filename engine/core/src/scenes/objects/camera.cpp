#include <scenes/objects/camera.h>

float32 Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::enable(Application &app) {
    renderer = [&](GraphicsContext *context) {
        glm::mat4 viewMatrix;
        getTransform().computeViewMatrix(&viewMatrix);
        int32 width, height;
        glfwGetWindowSize(context->getWindow(), &width, &height);
        auto projectionMatrix = glm::perspective(fieldOfView, (float) width / height, nearPlane, farPlane);;
        app.getContext()->render(projectionMatrix, viewMatrix);
    };
    app.getRenderEvent() += renderer;
}

void Camera::disable(Application &app) {
    app.getRenderEvent() -= renderer;
    renderer = nullptr;
}

void Camera::setFieldOfView(float32 fieldOfView) {
    Camera::fieldOfView = fieldOfView;
    reloadProjectionMatrix();
}

Camera::CameraTarget Camera::getTarget() const {
    return target;
}

void Camera::setTarget(Camera::CameraTarget target) {
    Camera::target = target;
}

Camera::Camera(Scene &scene) : SceneObject(scene) {
}

void Camera::reloadProjectionMatrix() {
}
