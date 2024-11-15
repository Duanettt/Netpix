#include "ResourceManager.h"



template<typename T>
T ResourceManager::GetResource(const std::string& userPrompt)
{
	auto it = textureBuffer.find(userPrompt);
	if (it != textureBuffer.end()) {
		return it->second;
	}
	return T();  // Return default-constructed T if not found
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
				// Need to fix this resource manager.
				Texture2D texture = LoadTexture(entry.path().generic_string().c_str());

				path parentDirectory = entry.path().parent_path();
				std::string parentDirectoryString = parentDirectory.filename().string();
				AddTexture(texture, parentDirectory);
			}
		}
}


void ResourceManager::AddTexture(Texture2D texture, path parentDirectory)
{
	//FIXME: Probably in the future make this way better for selecting which textures, right now having to go off numbers want to be able to tell like this png is an idle png.

	std::string parentDirectoryString = parentDirectory.filename().string();
	// We check the parentDirectory for if its equal to the previous directory we set if it isnt we reset our directory counter and insert.
	if (parentDirectoryString != previousDirectory || previousDirectory == "")
	{
		directoryCounter = 1;
		std::string parentDirectoryKey = parentDirectoryString + "_" + std::to_string(directoryCounter);
		textureBuffer.insert(std::make_pair(parentDirectoryKey, texture));
	}
	// Here if the previous directory and parentDirectory passed in are the same we increase the counter by 1 and insert into our unordered map.
	else
	{
		directoryCounter++;
		std::string parentDirectoryKey = parentDirectoryString + "_" + std::to_string(directoryCounter);
		textureBuffer.insert(std::make_pair(parentDirectoryKey, texture));
	}
	previousDirectory = parentDirectoryString;
}

void ResourceManager::printMap() {
	for (const auto& [key, value] : textureBuffer) {
		std::cout << key << ": " << &value << std::endl;
	}
}
