add_library(libjen
        include/jen/utility/clang_utility.h
        src/jen/utility/clang_utility.cpp
        #  Reflection
        include/jen/reflection/cxxclass.h
        src/jen/reflection/cxxclass.cpp
        include/jen/reflection/cxxparser.h
        src/jen/reflection/cxxparser.cpp
        include/jen/reflection/cxxcore.h
        include/jen/reflection/cxxmethod.h
        include/jen/reflection/cxxprimitives.h
        include/jen/reflection/cxxmacros.h
        src/jen/reflection/cxxmacros.cpp
        #  Generation
        include/jen/generation/cxxgenerator.h
        include/jen/generation/generated_source.h
        src/jen/generation/generated_source.cpp src/jen/generation/generation_context.cpp)
find_package(GFlags REQUIRED)
find_package(LibCLang REQUIRED)
target_link_libraries(libjen core gflags::gflags libclang)
target_include_directories(libjen
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
add_executable(jen src/jen.cpp src/jen/generation/serialization_generator.cpp)
target_include_directories(jen
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )
target_link_libraries(jen libjen)