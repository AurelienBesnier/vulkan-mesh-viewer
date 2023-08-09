cmake_minimum_required(VERSION 3.20)

include(FetchContent)
project(vulkanmeshviewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP)
if(NOT OpenMP_CXX_FOUND)
    message(WARNING "failed to find OpenMP CXX")
endif()
find_package(SDL2 REQUIRED)

find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-3.0)
include_directories(${GTK_INCLUDE_DIRS})

add_subdirectory(externs)

FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "./src/*")

set(IMGUI_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_vulkan.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp"
)

add_compile_options(-O3 -ftree-vectorize -march=native -floop-parallelize-all -ftree-parallelize-loops=4)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${IMGUI_SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS_OTHER})
target_include_directories(${PROJECT_NAME} PUBLIC src ${GTK_INCLUDE_DIRS})
FetchContent_MakeAvailable(fetch_vk_bootstrap)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX  vk-bootstrap::vk-bootstrap tinyobjloader stb_image ${SDL2_LIBRARIES} ${GTK_LIBRARIES} nativefiledialog)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
