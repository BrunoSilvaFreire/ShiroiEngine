set(JEN_LIBRARY
        include/jen/generator.h
        src/jen/generator.cpp
        include/jen/serialization_generator.h
        src/jen/serialization_generator.cpp
        include/jen/utility/clang_utility.h src/jen/utility/clang_utility.cpp)
set(JEN_EXECUTABLE

        src/jen.cpp
        )
set(JEN_ALL ${JEN_LIBRARY} ${JEN_EXECUTABLE})
add_executable(jen "${JEN_ALL}")
find_package(GFlags REQUIRED)
find_package(LibCLang REQUIRED)
target_link_libraries(jen core gflags::gflags libclang)
target_include_directories(jen PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )