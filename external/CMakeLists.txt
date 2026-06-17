# external/CMakeLists.txt
cmake_minimum_required(VERSION 3.25)

# ==============================================================================
# RAYLIB
# ==============================================================================
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(raylib)

if(NOT MSVC)
    target_compile_options(raylib INTERFACE -Wno-missing-field-initializers)
endif()

# ==============================================================================
# DEAR IMGUI + RLIMGUI 
# ==============================================================================
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
add_library(my_imgui_lib STATIC 
    "${IMGUI_DIR}/rlImGui.cpp"
    "${IMGUI_DIR}/imgui.cpp"
)
# 🟢 OPRAVA: Přidáno SYSTEM před PUBLIC. Všechny include složky z ImGui 
# budou pro tvou hlavní hru označené jako systémové (bez warningů).
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
