cmake_minimum_required(VERSION 3.25)
project(SuperTransportDeluxe CXX) # Pokud nepíšeš čisté C, C stačí odebrat

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Externí knihovny
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(external/raylib EXCLUDE_FROM_ALL)

# 2. Seznam zdrojových souborů (ruční výčet je jistota)
set(SOURCES
    src/main.cpp

    src/core/AssetManager.cpp
    src/core/Camera.cpp
    src/core/Logistic.cpp
    src/core/Map.cpp
    
    src/vehicle/Vehicle.cpp
    src/vehicle/VehicleManager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES}
    include/control/gui/GuiManager.hpp
    include/control/gui/GuiButton.hpp
    include/control/gui/GuiHelper.hpp
    include/control/gui/GuiDashboard.hpp)

# 3. Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# 4. Linkování (Raylib se postará o své include složky sám!)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# 5. Varování (Modernější zápis)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(raylib INTERFACE -Wno-missing-field-initializers)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall -Wextra -Wpedantic -Wshadow
    )
endif()