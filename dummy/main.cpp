#include <application/application.h>
#include <graphics/buffers/vertex_buffer.h>
#include <graphics/buffers/vertex_array.h>
#include <glog/logging.h>

int main() {
    Application app("Dummy Application");
    float32 vertexData[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0, 0.5F
    };

    VertexLayout layout;
    layout.push<float32>(2);
    VertexArray vao;
    vao.bind();
    uint16 indexData[] = {
            0, 1, 2
    };
    IndexBuffer ibo(1, indexData);
    VertexBuffer vbo(3, vertexData);
    vao.addLayout(layout, vbo);
    LOG(INFO) << "Finished";
    app.getTickEvent() += [&](float32 value) {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    };
    app.run();
}