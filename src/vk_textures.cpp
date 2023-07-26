#include <vk_textures.h>
#include <iostream>

#include <vk_init.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool vkutil::load_image_from_file(VulkanEngine& engine, const char* file, AllocatedImage& outImage)
{
	int texWidth, texHeight, texChannels;

	stbi_uc* pixels = stbi_load(file, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

	if (!pixels) {
		std::cout << "Failed to load texture file " << file << std::endl;
		return false;
	}

	return true;
}
