set(GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "Remove examples for glew")
set(GLFW_BUILD_TESTS FALSE CACHE BOOL "Remove tests for glew")
set(GLFW_INSTALL FALSE CACHE BOOL "Remove glfw install target")
add_subdirectory(${SHIROIENGINE_LIBS_DIR}/glfw ${CMAKE_BINARY_DIR}/glfw)