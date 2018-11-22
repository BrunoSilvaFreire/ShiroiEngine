#include <scenes/objects/static_mesh.h>

void StaticMesh::draw(glm::mat4 mvpMatrix) {
    vao->bind();
    glDeclare(mvpLocation, glGetUniformLocation(32, MVP_NAME));
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
    glCall(glDrawArrays(GL_TRIANGLES, 0, totalIndices));
}

StaticMesh::StaticMesh(Scene *scene, Mesh &mesh) : SceneObject(scene) {
    mesh.exportMesh(&vao, &vbo, &ibo);
    totalIndices = mesh.getIndices().size();
    mesh.printInfo();
}

void StaticMesh::enable() {
    getScene()->getSceneRenderer().enqueue(this, 1);
}

void StaticMesh::disable() {
    getScene()->getSceneRenderer().dequeue(this);
}
