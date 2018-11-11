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

typedef uint32 UUID;

class Scene {
private:
    Application *application;
    std::vector<SceneObject *> objects;
    Renderer sceneRenderer;
public:

    const std::vector<SceneObject *> &getObjects() const {
        return objects;
    }

    Application *getApplication() const {
        return application;
    }

    const Renderer &getSceneRenderer() const {
        return sceneRenderer;
    }

    UUID registerObject(SceneObject *object) {
        objects.push_back(object);
        // TODO: Create real unique id
        return reinterpret_cast<uint32 >(object);
    }
};

class SceneObject {
private:
    UUID uniqueId;
    Transform transform;
    Scene *scene;
public:
    const Transform &getTransform() const {
        return transform;
    }

    explicit SceneObject(Scene *scene) : transform() {
        uniqueId = scene->registerObject(this);
        this->scene = scene;
    }

    UUID getUniqueId() const {
        return uniqueId;
    }

    Scene *getScene() const {
        return scene;
    }

    virtual void enable() {}

    virtual void disable() {}

    virtual void initialize() {}

    virtual void terminate() {}
};

#endif
