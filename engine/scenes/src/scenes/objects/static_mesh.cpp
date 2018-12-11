#include <scenes/objects/static_mesh.h>

void StaticMesh::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    vao->bind();
    auto mvpMatrix = projectionMatrix * viewMatrix * transform.toModelMatrix();
    glDeclare(mvpLocation, glGetUniformLocation(material->getShaderId(), MVP_NAME));
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, reinterpret_cast<float32 *>(&mvpMatrix));
    glCall(glDrawElements(GL_TRIANGLES, (GLsizei) totalIndices, GL_UNSIGNED_INT, nullptr));
    vao->unbind();
}

StaticMesh::StaticMesh(Scene *scene, Mesh *mesh) : SceneObject(scene), material(mesh->getMaterial()) {
    mesh->exportMesh(&vao, &vbo, &ibo);
    totalIndices = mesh->getIndices().size();
    mesh->printInfo();
}

void StaticMesh::enable() {
    getScene()->getSceneRenderer().enqueue(this, 1);
}

void StaticMesh::disable() {
    getScene()->getSceneRenderer().dequeue(this);
}
