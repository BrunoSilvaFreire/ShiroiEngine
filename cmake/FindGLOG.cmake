set(WITH_GFLAGS OFF CACHE BOOL "Removes GFlags from glog")
set(BUILD_TESTING OFF CACHE BOOL "Remove glog things")
add_subdirectory(${SHIROIENGINE_LIBS_DIR}/glog ${CMAKE_BINARY_DIR}/glog)