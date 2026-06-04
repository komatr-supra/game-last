cmake_minimum_required(VERSION 3.25)

project(ProjectSTD CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Externí knihovny
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(external/raylib EXCLUDE_FROM_ALL)

# 2. Seznam zdrojových souborů (ruční výčet je jistota)
set(SOURCES
    src/main.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/Map.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES}
    include/Config.hpp
    include/AssetManager.hpp
    include/Camera.hpp
    include/WorldObject.hpp
    include/Map.hpp
    )

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

# Při vývoji vytvoříme odkaz na assets přímo v build složce
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
else()
    # Při ostrém vydání (Release/Publish) se assets reálně překopírují do výsledného balíčku
    install(DIRECTORY assets DESTINATION .)
endif()