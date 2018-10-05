#ifndef SHIROIENGINE_SCENE_H
#define SHIROIENGINE_SCENE_H

#include <vector>
#include <types.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
};

class Scene;

class SceneObject;

typedef uint32 UUID;

class Scene {
private:
    std::vector<SceneObject *> objects;
    Transform transform;
public:
    Transform &getTransform() {
        return transform;
    }

    const std::vector<SceneObject *> &getObjects() const {
        return objects;
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
public:
    explicit SceneObject(Scene &scene) {
        uniqueId = scene.registerObject(this);
    }

    UUID getUniqueId() const {
        return uniqueId;
    }
};

#endif
