#ifndef SHIROIENGINE_GRAPHICS_CONTEXT_H
#define SHIROIENGINE_GRAPHICS_CONTEXT_H

#include <types.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility/event.h>
#include <glm/glm.hpp>
#include <graphics/rendering.h>
#include <iterator>

/**
 * This represents all the resources created alongside OpenGL that might be useful for us
 */
class GraphicsContext {
private:
    GLFWwindow *window;

public:
    static const uint32 kDefaultWidth = 1920;
    static const uint32 kDefaultHeight = 1080;


    explicit GraphicsContext(
            string windowTitle,
            uint32 width = kDefaultWidth,
            uint32 height = kDefaultHeight
    );

    ~GraphicsContext();

    GLFWwindow *getWindow();
};

#endif
