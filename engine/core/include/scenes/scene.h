#ifndef SHIROIENGINE_SCENE_H
#define SHIROIENGINE_SCENE_H

#include <application/application.h>
#include <vector>
#include <types.h>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>

struct Transform {
private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
public:
    const glm::vec3 &getPosition() const {
        return position;
    }

    void setPosition(const glm::vec3 &position) {
        Transform::position = position;
    }

    const glm::quat &getRotation() const {
        return rotation;
    }

    void setRotation(const glm::quat &rotation) {
        Transform::rotation = rotation;
    }

    const glm::vec3 &getScale() const {
        return scale;
    }

    void setScale(const glm::vec3 &scale) {
        Transform::scale = scale;
    }

    void computeViewMatrix(glm::mat4 *result) const {
        glm::mat4 mat = glm::translate(glm::mat4(), position);
        mat *= glm::toMat4(rotation);
        mat *= glm::scale(mat, scale);

    }
};

class Scene;

class SceneObject;

#ifdef WIN32

#include <windows.h>

#else
typedef uint32 UUID;
#endif

class Scene {
private:
    Application *application;
    std::vector<SceneObject *> objects;
    Renderer sceneRenderer;
public:
    explicit Scene(Application *application);

    void enable();

    void disable();

    const std::vector<SceneObject *> &getObjects() const;

    Application *getApplication() const;

    const Renderer &getSceneRenderer() const;

    UUID registerObject(SceneObject *object);
};

class SceneObject {
private:
    UUID uniqueId;
    Transform transform;
    Scene *scene;
public:
    const Transform &getTransform() const;

    explicit SceneObject(Scene *scene);

    UUID getUniqueId() const;

    Scene *getScene() const;

    virtual void enable();

    virtual void disable();

    virtual void initialize();

    virtual void terminate();
};

#endif
