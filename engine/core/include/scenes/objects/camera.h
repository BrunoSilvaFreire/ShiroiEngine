#ifndef SHIROIENGINE_CAMERA_H
#define SHIROIENGINE_CAMERA_H

#include <scenes/scene.h>
#include <application/application.h>
#include <glm/glm.hpp>

class Camera : SceneObject {
public:
    enum CameraTarget {
        SCREEN,
        EMBEDDED_TEXTURE,
        EXTERNAL_TEXTURE
    };
private:
    CameraTarget target;
    glm::mat4 projectionMatrix;
    uint32 embeddedTextureId;

    void renderScene(Scene &scene) {
        for (auto obj : scene.getObjects()) {
            //obj->render(projectionMatrix, viewMatrix);
        }
    }

public:
    CameraTarget getTarget() const {
        return target;
    }

    void setTarget(CameraTarget target) {
        Camera::target = target;
    }

    Camera(Application &app, Scene &scene) : SceneObject(scene) {
        app.getRenderEvent() += [&](GraphicsContext *context, GLFWwindow *window) {
            renderScene(scene);
        };
    }
};

#endif
