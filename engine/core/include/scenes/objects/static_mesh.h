#ifndef SHIROIENGINE_STATIC_MESH_H
#define SHIROIENGINE_STATIC_MESH_H

#include <scenes/scene.h>
#include <graphics/mesh.h>
class StaticMesh : SceneObject, IDrawable {
public:
    StaticMesh(Scene *scene, const Mesh &mesh);

private:
    void draw(glm::mat4 viewMatrix) override;
};

#endif
