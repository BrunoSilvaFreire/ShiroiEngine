add_executable(jen include/parser.h src/parser.cpp src/generator.cpp )
find_package(GFlags REQUIRED)
target_link_libraries(jen core gflags::gflags)
target_include_directories(jen PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )