#ifndef SHIROIENGINE_GRAPHICS_CONTEXT_H
#define SHIROIENGINE_GRAPHICS_CONTEXT_H

#include <types.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility/event.h>
#include <glm/glm.hpp>
#include <graphics/rendering.h>
#include <iterator>

class GraphicsContext {
private:
    GLFWwindow *window;

public:
    static const uint32 kDefaultWidth = 800;
    static const uint32 kDefaultHeight = 400;


    explicit GraphicsContext(
            string windowTitle,
            uint32 width = kDefaultWidth,
            uint32 height = kDefaultHeight
    );

    ~GraphicsContext();

    GLFWwindow *getWindow();

    static void render(std::vector<IDrawable *> &objects, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
        for (IDrawable *drawable : objects) {
            drawable->draw(viewMatrix, projectionMatrix);
        }
    }
};

#endif
