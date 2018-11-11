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
    float32 fieldOfView;
    float32 nearPlane, farPlane;
    Event<float32>::EventListener renderer;

    void reloadProjectionMatrix();

public:
    float32 getFieldOfView() const;

    void setFieldOfView(float32 fieldOfView);

    CameraTarget getTarget() const;

    void setTarget(CameraTarget target);

    Camera(Scene *scene);

    virtual void enable() override;

    virtual void disable() override;
};

#endif
