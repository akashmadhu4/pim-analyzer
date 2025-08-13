cmake_minimum_required(VERSION 3.13)
project(PIMAnalyzer)

# LLVM submodule
set(LLVM_DIR "${CMAKE_SOURCE_DIR}/llvm-project/llvm/build/lib/cmake/llvm")
set(Clang_DIR "${CMAKE_SOURCE_DIR}/llvm-project/llvm/build/lib/cmake/clang")

list(INSERT CMAKE_PREFIX_PATH 0 "${CMAKE_SOURCE_DIR}/llvm-project/build")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVM headers: ${LLVM_INCLUDE_DIRS}")
message(STATUS "Using Clang libraries: ${CLANG_LIBS}")

# Adding executable
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.cc"  
)

add_executable(pim-analyzer ${SOURCES})

# Include directories
target_include_directories(pim-analyzer PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(pim-analyzer PRIVATE
    -fno-rtti  # Disable RTTI
)

# Link against required libraries
target_link_libraries(pim-analyzer PRIVATE
    clangAST
    clangAnalysis
    clangBasic
    clangFrontend
    clangStaticAnalyzerFrontend
    clangTooling
    LLVMSupport
    LLVMOption
)

# Compiler flags
set_target_properties(pim-analyzer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)