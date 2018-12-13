add_executable(dummy main.cpp ../test.hpp)
target_link_libraries(dummy core)
install(TARGETS dummy
        DESTINATION ${CMAKE_INSTALL_PREFIX}/dummy
        )