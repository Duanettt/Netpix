cmake_minimum_required(VERSION 3.30)
# Set the project name
project(Netpix)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Raylib (assumed to be installed via vcpkg or system package manager)
find_package(raylib REQUIRED)
find_package(OpenGL REQUIRED)

# Define the executable target
add_executable(${PROJECT_NAME})

# Collect all source files (.cpp and .h) from subdirectories
file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.h
)

# Add source files to the target
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})

# Include directories (for headers)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Link libraries (link Raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Set the working directory to the root of your project
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")


# Print the VS_DEBUGGER_WORKING_DIRECTORY property for the target
get_target_property(WORKING_DIR ${PROJECT_NAME} VS_DEBUGGER_WORKING_DIRECTORY)
message(STATUS "Configured working directory for target '${PROJECT_NAME}': ${WORKING_DIR}")


# Define texture and sprite directories
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR} ${CMAKE_BINARY_DIR}/res
)

# Print resource directories for debugging
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
    message(STATUS "Adding resource directory: ${RESOURCE_DIR}")
endforeach()