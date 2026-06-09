cmake_minimum_required(VERSION 3.25)

project(ProjectSTD CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================================================
# 1. Externí knihovny
# ==============================================================================
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(external/raylib EXCLUDE_FROM_ALL)
add_subdirectory(external/tweeny-3.2.1 EXCLUDE_FROM_ALL)
# ==============================================================================
# 2. Seznam zdrojových souborů
# ==============================================================================
set(SOURCES
    src/main.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/Map.cpp
    src/vehicle/VehicleManager.cpp
    src/vehicle/Vehicle.cpp
    #src/vehicle/tasks/VehicleTaskIdle.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES}
    include/Config.hpp
    include/AssetManager.hpp
    include/Camera.hpp
    #include/WorldObject.hpp
    include/Map.hpp
    #include/World.hpp
    include/vehicle/VehicleManager.hpp
    include/vehicle/Vehicle.hpp
    include/vehicle/VehicleDefinition.hpp
    #include/vehicle/tasks/VehicleTaskBase.hpp
)

# ==============================================================================
# 3. Include directories (Nastavení cest pro tvůj projekt i externí věci)
# ==============================================================================
# Tvoje vlastní include složka
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)



# ==============================================================================
# 4. Linkování (Raylib se o své include složky stará sám)
# ==============================================================================
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tweeny)

# ==============================================================================
# 5. Varování kompilátoru
# ==============================================================================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(raylib INTERFACE -Wno-missing-field-initializers)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall -Wextra -Wpedantic -Wshadow
    )
endif()

# ==============================================================================
# 6. Správa Assetů (Symlink pro Debug, kopírování pro Release)
# ==============================================================================
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
else()
    install(DIRECTORY assets DESTINATION .)
endif()