#include <scenes/objects/camera.h>

float32 Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::enable() {
    auto scene = getScene();
    renderer = [&](float32 deltaTime) {
        LOG(INFO) << "Drawing";
        glm::mat4 vpMatrix;
        getTransform().computeViewMatrix(&vpMatrix);
        int32 width, height;
        LOG(INFO) << "Getting window size @ " << scene;
        LOG(INFO) << "Application = " << scene->getApplication();
        auto isNull = scene->getApplication()->getContext() == nullptr;
        LOG(INFO) << "Is null @ " << isNull;
        LOG(INFO) << "Context = " << scene->getApplication()->getContext();
        LOG(INFO) << "Window = " << scene->getApplication()->getContext()->getWindow();
        /*glfwGetWindowSize(scene->getApplication()->getContext()->getWindow(), &width, &height);
        vpMatrix *= glm::perspective(fieldOfView, (float) width / height, nearPlane, farPlane);
        LOG(INFO) << "rendering";
        scene->getSceneRenderer().render(0, vpMatrix);*/
        LOG(INFO) << "Drawed";
    };
    //scene->getApplication()->getLateUpdateEvent() += &renderer;
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
