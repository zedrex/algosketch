# Set a minimum CMake version
cmake_minimum_required(VERSION 3.1)

# Define project name
project(AlgoSketch)

# Look for the SFML components
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

# Define a list of header directories
set(HEADERS
    "include/"
)

# Include the header file directories
include_directories(${HEADERS})

# Define a list of our source files
set(SOURCES

    # AlgoSketch
    "src/main.cpp"

    # Manager headers
    "src/managers/application.cpp"
    "src/managers/state_manager.cpp"
    "src/managers/window_manager.cpp"
    "src/managers/event_manager.cpp"
    "src/managers/resource_manager.cpp"

    "include/managers/application.hpp"
    "include/managers/state_manager.hpp"
    "include/managers/window_manager.hpp"
    "include/managers/event_manager"
    "include/managers/resource_manager.hpp"

    # State headers
    "src/states/state.cpp"
    "src/states/main_menu.cpp"
    "src/states/new_sketch_menu.cpp"
    "src/states/help_menu.cpp"
    "src/states/credits_menu.cpp"
    "src/states/array_algorithm_menu.cpp"
    "src/states/array_sketch_menu.cpp"
    "src/states/graph_algorithm_menu.cpp"
    "src/states/graph_sketch_menu.cpp"    
    "src/states/grid_algorithm_menu.cpp"
    "src/states/grid_sketch_menu.cpp"

    "include/states/state.hpp"
    "include/states/main_menu.hpp"
    "include/states/new_sketch_menu.hpp"
    "include/states/help_menu.hpp"
    "include/states/credits_menu.hpp"
    "include/states/array_algorithm_menu.hpp"
    "include/states/array_sketch_menu.hpp"
    "include/states/graph_algorithm_menu.hpp"
    "include/states/graph_sketch_menu.hpp"
    "include/states/grid_algorithm_menu.hpp"
    "include/states/grid_sketch_menu.hpp"

    # State element headers
    "src/state_elements/state_element.cpp"
    "src/state_elements/button.cpp"
    "src/state_elements/panel.cpp"
    "src/state_elements/text_form.cpp"

    "include/state_elements/state_element.hpp"
    "include/state_elements/button.hpp"
    "include/state_elements/panel.hpp"
    "include/state_elements/text_form.hpp"

    # Sketch headers
    "src/sketches/sketch_container.cpp"
    "src/sketches/array.cpp"
    "src/sketches/graph.cpp"
    "src/sketches/grid.cpp"

    "include/sketches/sketch_container.hpp"
    "include/sketches/array.hpp"
    "include/sketches/graph.hpp"
    "include/sketches/grid.hpp"

    "include/debugger.hpp"
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
