#ifndef SHIROIENGINE_STATIC_MESH_H
#define SHIROIENGINE_STATIC_MESH_H

#include <scenes/scene.h>
#include <graphics/mesh.h>

#define MVP_NAME "mvpMatrix"

class StaticMesh : SceneObject, IDrawable {
private:
    VertexArray *vao;
    VertexBuffer *vbo;
    IndexBuffer *ibo;
    uint32 totalIndices;
public:
    StaticMesh(Scene *scene, Mesh &mesh);

    void draw(glm::mat4 mvpMatrix) override;

    void enable() override;

    void disable() override;
};

#endif
