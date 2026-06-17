cmake_minimum_required(VERSION 3.25)

project(TransportWars CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===== Subdirectories (other CmakeLists.txt) =====
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external")

# ===== Source files =====
include(sources.cmake)
add_executable(${PROJECT_NAME} ${SOURCES}
    
    )

# ===== Include =====
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src/common")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall -Wextra -Wpedantic -Wshadow
    )
endif()

# ===== External libs =====
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    my_imgui_lib
    tweeny
    my_json_lib
    my_rlights_lib
)

# ===== Assets (use symlink for develop, copy asset folder on Release) =====
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
else()
    install(DIRECTORY assets DESTINATION .)
endif()