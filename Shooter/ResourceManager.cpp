#include "ResourceManager.h"



template<typename T>
T ResourceManager::GetResource()
{
	return T();
}

ResourceManager::ResourceManager()
{
	LoadAllTextures();
}

void ResourceManager::LoadAllTextures()
{
	if(exists(resourcePath))
		for (const auto& entry : recursive_directory_iterator(resourcePath))
		{
			const auto fileName = entry.path().filename().string();
			if (entry.is_regular_file() && entry.path().extension() == ".png")
			{
				std::cout << "Found PNG file: " << entry.path() << std::endl;

				Texture2D one = LoadTexture("res/character/main/Attack.png");
				path parentDirectory = entry.path().parent_path();
				std::cout << "Located in directory: " << parentDirectory.filename().string() << std::endl;
			}
		}
}
