#include <scenes/scene.h>

SceneObject::SceneObject(Scene *scene) : transform() {
    uniqueId = scene->registerObject(this);
    this->scene = scene;
}

const Transform &SceneObject::getTransform() const {
    return transform;
}

UUID SceneObject::getUniqueId() const {
    return uniqueId;
}

Scene *SceneObject::getScene() const {
    return scene;
}

void SceneObject::enable() {}

void SceneObject::disable() {}

void SceneObject::initialize() {}

void SceneObject::terminate() {}

Application *Scene::getApplication() const {
    return application;
}

const std::vector<SceneObject *> &Scene::getObjects() const {
    return objects;
}

void Scene::disable() {
    for (SceneObject *obj : objects) {
        obj->disable();
    }
}

void Scene::enable() {
    for (SceneObject *obj : objects) {
        obj->enable();
    }
}

const Renderer &Scene::getSceneRenderer() const {
    return sceneRenderer;
}

UUID Scene::registerObject(SceneObject *object) {
    objects.push_back(object);
    // TODO: Create real unique id
#ifdef WIN32
    UUID uuid;
    CoCreateGuid(&uuid);
    return uuid;
#else
    static_assert(false);
#endif
}

Scene::Scene(Application *application) : application(application), sceneRenderer(), objects() {
}
