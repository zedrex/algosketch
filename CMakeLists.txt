# Set a minimum CMake version
cmake_minimum_required(VERSION 3.1)

# Define project name
project(AlgoSketch)

# Look for the SFML components
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

# Define a list of header directories
set(HEADERS
    "lib/algo" 
    "lib/sketch"
)

# Include the header file directories
include_directories(${HEADERS})

# Define a list of our source files
set(SOURCES
    "src/main.cpp"

    "src/sketch/test.cpp"

    "lib/sketch/test.hpp"
)

# Set executable path to bin
set(EXECUTABLE_OUTPUT_PATH "../bin/")

# Define target executable based on the source files above
add_executable(AlgoSketch ${SOURCES})

# Link executable to SFML and its dependencies
target_link_libraries(AlgoSketch sfml-audio sfml-graphics sfml-window sfml-system)
