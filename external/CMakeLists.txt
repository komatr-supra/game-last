cmake_minimum_required(VERSION 3.25)

# ==============================================================================
# RAYLIB (Statická knihovna)
# ==============================================================================
# Vynutíme statický build Raylibu
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

add_subdirectory(raylib-6.0)

if(NOT MSVC)
    target_compile_options(raylib INTERFACE -Wno-missing-field-initializers)
endif()

# ==============================================================================
# DEAR IMGUI + RLIMGUI 
# ==============================================================================
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# Podmínka pro demo: zahrnout pouze pokud není Release build
set(IMGUI_SOURCES 
    "${IMGUI_DIR}/rlImGui.cpp"
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND IMGUI_SOURCES "${IMGUI_DIR}/imgui_demo.cpp")
endif()

add_library(my_imgui_lib STATIC ${IMGUI_SOURCES})

target_include_directories(my_imgui_lib SYSTEM PUBLIC ${IMGUI_DIR})
target_link_libraries(my_imgui_lib PUBLIC raylib)

if(NOT MSVC)
    target_compile_options(my_imgui_lib PRIVATE -w) 
endif()

# ==============================================================================
# TWEENY
# ==============================================================================
add_subdirectory(tweeny)
if(TARGET tweeny)
    set_target_properties(tweeny PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES 
        "$<TARGET_PROPERTY:tweeny,INTERFACE_INCLUDE_DIRECTORIES>"
    )
endif()
# ==============================================================================
# JSON.HPP (Nlohmann JSON - Header-only)
# ==============================================================================
add_library(my_json_lib INTERFACE)
target_include_directories(my_json_lib SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")


# ==============================================================================
# 5. RLIGHTS.H
# ==============================================================================
add_library(my_rlights_lib INTERFACE)
target_include_directories(my_rlights_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/rlights")
