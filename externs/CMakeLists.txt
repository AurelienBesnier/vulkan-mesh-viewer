add_library(tinyobjloader INTERFACE)
target_compile_definitions(tinyobjloader INTERFACE TINYOBJLOADER_IMPLEMENTATION)
target_include_directories(tinyobjloader SYSTEM INTERFACE tinyobjloader)

add_library(stb_image INTERFACE)
target_include_directories(stb_image SYSTEM INTERFACE stb_image)

add_subdirectory(nativefiledialog)
