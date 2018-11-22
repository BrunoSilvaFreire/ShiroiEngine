#ifndef SHIROIENGINE_CAMERA_H
#define SHIROIENGINE_CAMERA_H

#include <scenes/scene.h>
#include <application/application.h>
#include <glm/glm.hpp>
#include <serialization/annotation_macros.h>

class Camera : SceneObject {
public:
    enum CameraTarget {
        SCREEN,
        EMBEDDED_TEXTURE,
        EXTERNAL_TEXTURE
    };
private:
    SERIALIZE()
    CameraTarget target;

    SERIALIZE()
    float32 fieldOfView;

    SERIALIZE()
    float32 nearPlane, farPlane;

    Event<float32>::EventListener renderer;

    void reloadProjectionMatrix();

public:
    explicit Camera(Scene *scene);

    float32 getFieldOfView() const;

    void setFieldOfView(float32 fieldOfView);

    CameraTarget getTarget() const;

    void setTarget(CameraTarget target);


    void enable() override;

    void disable() override;
};

#endif
