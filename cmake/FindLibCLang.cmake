find_path(LLVM_INSTALL_DIR LLVM)
set(LLVM_ROOT ${LLVM_INSTALL_DIR}/LLVM)
add_library(libclang STATIC IMPORTED)
target_include_directories(libclang
        INTERFACE
        $<BUILD_INTERFACE:${LLVM_ROOT}/include/>)
set_target_properties(libclang
        PROPERTIES
        IMPORTED_LOCATION ${LLVM_ROOT}/lib/libclang.lib)