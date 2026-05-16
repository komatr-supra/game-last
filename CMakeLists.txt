cmake_minimum_required(VERSION 3.25)

project(My3DARPG C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Nastavení Raylibu
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# 2. Přidání submodulu (tohle zkompiluje raylib.a / raylib.lib)
add_subdirectory(external/raylib EXCLUDE_FROM_ALL SYSTEM)

# 3. Definice tvého spustitelného souboru
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES}
    include/CameraController.hpp
    external/json.hpp)

# 4. KLÍČOVÝ KROK: Říct kompilátoru, kde jsou .h soubory
# Musíme zahrnout složku 'src' uvnitř submodulu raylib
target_include_directories(${PROJECT_NAME} PRIVATE 
    include 
    external/raylib/src
    external
)

# 5. Linkování
target_link_libraries(${PROJECT_NAME} raylib)

# 6. Linux fix (pro Ubuntu na notebooku)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall           # Zapne základní varování
        -Wextra         # Zapne další užitečná varování
        -Wpedantic      # Trvá na striktním dodržování standardu C11
        -Wshadow        # Varuje, když si pojmenuješ proměnnou stejně jako globální
        -Wstrict-prototypes # Hlídá správné definice funkcí
    )
endif()