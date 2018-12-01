#include <services/builtin/embed_shapes.h>
#include <iostream>

glm::vec3 EmbedShapes::cubeVertices[8] = {
        glm::vec3(.5F, -.5F, .5F),
        glm::vec3(-.5F, -.5F, .5F),
        glm::vec3(.5F, -.5F, -.5F),
        glm::vec3(-.5F, -.5F, -.5F),
        glm::vec3(.5F, .5F, .5F),
        glm::vec3(-.5F, .5F, .5F),
        glm::vec3(.5F, .5F, -.5F),
        glm::vec3(-.5F, .5F, -.5F)
};

uint32 EmbedShapes::cubeIndices[36] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
};

glm::vec3 EmbedShapes::quadVertices[4] = {
        glm::vec3(0.5, 0.5, 0),
        glm::vec3(0.5, -0.5, 0),
        glm::vec3(-0.5, -0.5, 0),
        glm::vec3(-0.5, 0.5, 0)
};

uint32 EmbedShapes::quadIndices[6] = {
        0, 1, 2, 2, 3, 0
};

inline VertexLayout createSimpleLayout(uint8 components);

VertexLayout createSimpleLayout(uint8 components) {
    auto l = VertexLayout();
    // Position element
    l.push<float32>(components);
    return l;
}


EmbedShapes::EmbedShapes() {
    embedLayout3D = createSimpleLayout(3);
    embedLayout2D = createSimpleLayout(2);
    //TODO: Remove and load paths properly
    auto path = "../resources/core/shaders";
    ShaderProgram *program;
    program = ShaderProgram::defaultProgram(path);
    embedMaterial = new Material(program);
    LOG(INFO) << "Successfully loaded shaders.";
    program->bind();
    cube = new Mesh(
            embedLayout3D, (void *) cubeVertices, 8,
            std::vector<uint32>(cubeIndices, cubeIndices + 36), embedMaterial
    );
    quad = new Mesh(
            embedLayout3D, (void *) quadVertices, 4,
            std::vector<uint32>(quadIndices, quadIndices + 6), embedMaterial
    );
}

Mesh *EmbedShapes::getCube() const {
    return cube;
}

Mesh *EmbedShapes::getQuad() const {
    return quad;
}
