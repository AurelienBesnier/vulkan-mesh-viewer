#!/usr/bin/bash

# Build the shaders
echo "Compiling shaders ..."
shader_dir_vert=`ls ./shaders/*.vert`
shader_dir_frag=`ls ./shaders/*.frag`
for entry in $shader_dir_vert
do
  glslc -o "$entry.spv" "$entry"
done

for entry in $shader_dir_frag
do
  glslc -o "$entry.spv" "$entry"
done

echo "Done!"

# Build the application
echo "Building application..."
cmake -S ./ -B ./build
cmake --build ./build --target all -- -j
echo "Done!"

./build/vulkanmeshviewer
