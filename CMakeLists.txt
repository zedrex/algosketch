# Set a minimum CMake version
cmake_minimum_required(VERSION 3.1)

# Define project name
project(AlgoSketch)

# Look for the SFML components
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

# Define a list of header directories
set(HEADERS
    "lib/"
)

# Include the header file directories
include_directories(${HEADERS})

# Define a list of our source files
set(SOURCES
    "src/main.cpp"
    "src/application.cpp"
    "src/state_manager.cpp"
    "src/window_manager.cpp"
    "src/event_manager.cpp"
    "src/resource_manager.cpp"
    "src/state.cpp"
    "src/state_element.cpp"

    "lib/application.hpp"
    "lib/state_manager.hpp"
    "lib/window_manager.hpp"
    "lib/event_manager"
    "lib/resource_manager.hpp"
    "lib/state.hpp"
    "lib/state_element.hpp"


    "lib/debugger.hpp"
)

# Set executable path to bin
set(EXECUTABLE_OUTPUT_PATH "../bin/")

# Define target executable based on the source files above
add_executable(AlgoSketch ${SOURCES})

# Add the assets to the binary folder
file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/
    DESTINATION "../bin/assets/")

# Link executable to SFML and its dependencies
target_link_libraries(AlgoSketch sfml-audio sfml-graphics sfml-window sfml-system)
