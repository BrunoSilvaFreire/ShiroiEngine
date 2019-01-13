add_library(libjen
        include/jen/queued_class.h
        include/jen/generator.h
        include/jen/serialization_generator.h
        src/jen/serialization_generator.cpp
        include/jen/utility/clang_utility.h
        src/jen/utility/clang_utility.cpp
        src/jen/queued_class.cpp
        include/jen/generator.h
        include/jen/utility/generated_scope.h
        src/jen/utility/generated_scope.cpp
        include/jen/reflection/cxxclass.h
        src/jen/reflection/cxxclass.cpp
        include/jen/reflection/cxxparser.h
        src/jen/reflection/cxxparser.cpp
        include/jen/reflection/cxxcore.h
        include/jen/reflection/cxxmethod.h
        include/jen/reflection/cxxprimitives.h
        include/jen/reflection/cxxmacros.h src/jen/reflection/cxxmacros.cpp)
find_package(GFlags REQUIRED)
find_package(LibCLang REQUIRED)
target_link_libraries(libjen core gflags::gflags libclang)
target_include_directories(libjen
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
add_executable(jen src/jen.cpp include/jen/reflection/cxxmethod.h include/jen/reflection/cxxprimitives.h)
target_link_libraries(jen libjen)