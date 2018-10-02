#ifndef SHIROIENGINE_GRAPHICS_CONTEXT_H
#define SHIROIENGINE_GRAPHICS_CONTEXT_H

#include <types.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
};

#endif
