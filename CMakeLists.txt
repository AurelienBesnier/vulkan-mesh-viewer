cmake_minimum_required(VERSION 3.20)

include(FetchContent)
project(vulkanmeshviewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP)
if(NOT OpenMP_CXX_FOUND)
    message(WARNING "failed to find OpenMP CXX")
endif()
find_package(SDL2 REQUIRED)

find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

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

"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_vulkan.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
FetchContent_MakeAvailable(fetch_vk_bootstrap)
target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX  vk-bootstrap::vk-bootstrap tinyobjloader stb_image ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
