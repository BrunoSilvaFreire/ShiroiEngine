#ifndef SHIROIENGINE_SCENE_H
#define SHIROIENGINE_SCENE_H

#include <application/application.h>
#include <vector>
#include <types.h>
#include <glm/glm.hpp>
#include <serialization/annotation_macros.h>
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

struct Transform {
public:
    explicit Transform(
            const glm::vec3 &position = glm::vec3(0, 0, 0),
            const glm::quat &rotation = glm::quat(1, 0, 0, 0),
            const glm::vec3 &scale = glm::vec3(1, 1, 1)
    ) : position(position),
        rotation(rotation),
        scale(scale) {}

    SERIALIZE()
    glm::vec3 position;

    SERIALIZE()
    glm::quat rotation;

    SERIALIZE()
    glm::vec3 scale;

    glm::mat4 toViewMatrix() const {
        return glm::lookAt(position, position + getForward(), glm::vec3(0, 1, 0));
        //return glm::translate(glm::mat4(1), position) * glm::toMat4(rotation);
    }

    glm::mat4 toModelMatrix() const {
        auto mat = glm::toMat4(rotation) * glm::scale(glm::mat4(1), scale);
        return glm::translate(glm::mat4(1), position) * mat;
    };

    glm::vec3 getForward() const {
        return rotation * glm::vec3(0, 0, 1);
    }

    glm::vec3 getUp() const {
        return rotation * glm::vec3(0, 1, 0);
    }

    glm::vec3 getRight() const {
        return rotation * glm::vec3(1, 0, 0);
    }

    friend std::ostream &operator<<(std::ostream &os, const Transform &transform) {
        return os << "Transform(" <<
                  "position: " << glm::to_string(transform.position) <<
                  ", rotation: " << glm::to_string(transform.rotation) <<
                  ", scale: " << glm::to_string(transform.scale) <<
                  ")";
    }
};

class Scene;

class SceneObject;

#ifdef WIN32

#include <windows.h>
#include <ostream>

#else
typedef uint32 UUID;
#endif

class Scene {
private:
    Application *application;
    std::vector<SceneObject *> objects;
    Renderer sceneRenderer;
public:
    explicit Scene(Application *app);

    void enable();

    void disable();

    const std::vector<SceneObject *> &getObjects() const;

    Application *getApplication() const;

    Renderer &getSceneRenderer();

    UUID registerObject(SceneObject *object);
};

class SceneObject {
private:
    UUID uniqueId;
    Scene *scene;
public:
    Transform transform;

    explicit SceneObject(Scene *scene);

    UUID getUniqueId() const;

    Scene *getScene() const;

    virtual void enable();

    virtual void disable();

    virtual void initialize();

    virtual void terminate();

    friend std::ostream &operator<<(std::ostream &os, const SceneObject &object);

    friend std::ostream &operator<<(std::ostream &os, const SceneObject *object);
};

#endif
