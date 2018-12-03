#include <scenes/objects/camera.h>
#include <glm/gtx/string_cast.hpp>
#include <maths/angles.h>

float32 Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::enable() {
    renderer = [&](float32 deltaTime) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        int32 width, height;
        auto scene = getScene();
        glfwGetWindowSize(scene->getApplication()->getContext()->getWindow(), &width, &height);
        auto aspect = (float) width / height;
        auto viewMatrix = transform.toViewMatrix();
        auto perspectiveMatrix = glm::perspective(fieldOfView * DEG_TO_RAD, aspect, nearPlane, farPlane);
        scene->getSceneRenderer().render(0, viewMatrix, perspectiveMatrix);
    };
    auto scene = getScene();
    scene->getApplication()->getMainStepFunction().getLateStep() += &renderer;
}

void Camera::disable() {
    getScene()->getApplication()->getMainStepFunction().getLateStep() -= &renderer;
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

Camera::Camera(Scene *scene, float32 nearPlane, float32 farPlane, float32 fov) : SceneObject(scene),
                                                                                 nearPlane(nearPlane),
                                                                                 farPlane(farPlane), fieldOfView(fov) {
}

void Camera::reloadProjectionMatrix() {
}
