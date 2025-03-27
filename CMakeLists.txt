cmake_minimum_required(VERSION 3.10)
project(flappy-bird)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 and SDL2_image using both module and config modes
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Print found paths for debugging
message(STATUS "SDL2 include dir: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_image include dir: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")

add_executable(flappy-bird 
    src/Main.cpp
    src/Renderer.cpp
    src/Window.cpp
)

# Include directories
target_include_directories(flappy-bird PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# Link libraries - explicit linking
target_link_libraries(flappy-bird PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

# For some systems, you might need to explicitly add these:
target_link_libraries(flappy-bird PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})