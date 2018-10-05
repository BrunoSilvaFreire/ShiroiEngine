#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>
#include <graphics/shaders/shader_program.h>

const string shaderPath = "../resources/core/shaders";

int main() {
    Application app("Dummy Application");
    float32 vertexData[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0, 0.5F
    };

    ShaderProgram *program = ShaderProgram::defaultProgram(shaderPath);
    LOG(INFO) << "Successfully loaded shaders.";
    program->bind();
    VertexLayout layout;
    layout.push<float32>(2);
    VertexArray vao;
    vao.bind();
    uint16 indexData[] = {
            0, 1, 2
    };
    IndexBuffer ibo(3, indexData);
    auto s = 6 * sizeof(float32);
    VertexBuffer vbo(s, vertexData);
    vao.addLayout(layout, vbo);
    app.getTickEvent() += [&](float32 value) {
        glCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    };
    app.run();
}