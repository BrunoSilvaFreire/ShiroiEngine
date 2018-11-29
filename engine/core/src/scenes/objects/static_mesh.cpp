#include <scenes/objects/static_mesh.h>

void StaticMesh::draw(glm::mat4 mvpMatrix) {
    vao->unbind();
    ibo->unbind();
    vbo->unbind();
    glPrintBoundTargets();
    vao->bind();
    ibo->bind();
    vbo->bind();
    glPrintBoundTargets();
    glCall(glUseProgram(material->getShaderId()));
    glDeclare(mvpLocation, glGetUniformLocation(material->getShaderId(), MVP_NAME));
    /*LOG(INFO) << "Drawing mesh w/ " << mvpLocation;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);*/
    LOG(INFO) << "Drawing @ " << totalIndices;
    glCall(glDrawElements(GL_TRIANGLES, (GLsizei) totalIndices, GL_UNSIGNED_INT, nullptr));
    vao->unbind();
    glPrintBoundTargets();
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
