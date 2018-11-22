#include <scenes/objects/camera.h>

float32 Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::enable() {
    renderer = [&](float32 deltaTime) {
        glm::mat4 vpMatrix;
        getTransform().computeViewMatrix(&vpMatrix);
        int32 width, height;
        auto scene = getScene();
        glfwGetWindowSize(scene->getApplication()->getContext()->getWindow(), &width, &height);
        vpMatrix *= glm::perspective(fieldOfView, (float) width / height, nearPlane, farPlane);
        scene->getSceneRenderer().render(0, vpMatrix);
    };
    auto scene = getScene();
    scene->getApplication()->getMainStepFunction().getLateStep() += &renderer;
}

void Camera::disable() {
    //getScene()->getApplication()->getLateUpdateEvent() -= &renderer;
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

Camera::Camera(Scene *scene) : SceneObject(scene) {
}

void Camera::reloadProjectionMatrix() {
}
