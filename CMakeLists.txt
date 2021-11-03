CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)
project(fgs)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_definitions(-DANTLR4CPP_STATIC)

include(ExternalAntlr4Cpp)
set(ANTLR_EXECUTABLE /usr/local/lib/antlr-4.9.2-complete.jar)
set(ANTLR4_RUNTIME_LIBRARIES /usr/local/lib)

find_package(ANTLR REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

antlr_target(C.g4 BOTH VISITOR)

include_directories(${ANTLR_C_OUTPUT_DIR})

# Now build our tools
add_executable(fgs
	main.cpp
	${ANTLR_C_CXX_OUTPUTS}
	${SOURCE_FILES}
)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(fgs antlr4_static ${llvm_libs})

