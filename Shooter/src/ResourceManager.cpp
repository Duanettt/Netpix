#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	LoadAllTextures();
	printMap();
}

void ResourceManager::LoadAllTextures()
{
	if(exists(resourcePath))
		for (const auto& entry : recursive_directory_iterator(resourcePath))
		{
			const auto fileName = entry.path().filename().string();
			if (entry.is_regular_file() && entry.path().extension() == ".png")
			{
				// FIXME: Soon need to do a lot of error handling in general.
				Texture2D texture = LoadTexture(entry.path().generic_string().c_str());
				// Get parent path
				path parentDirectory = entry.path().parent_path();
				// Pass to texture function so we can add to our map key.
				AddTexture(texture, parentDirectory);
			}

			if (entry.is_regular_file() && entry.path().extension() == ".mp3")
			{
				Music music = LoadMusicStream(entry.path().generic_string().c_str());
				// Get parent path
				path parentDirectory = entry.path().parent_path();
				// Pass to music function so we can add to our map key.
				AddMusic(music, parentDirectory);
			}
		}
}

// FIXME: Possibly in the near future AddMusic and AddTexture can be made into one function by utilising this->buffer of our choice hardcoded will do this another time.
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

void ResourceManager::AddMusic(Music music, path parentDirectory)
{

	std::string parentDirectoryString = parentDirectory.filename().string();
	// We check the parentDirectory for if its equal to the previous directory we set if it isnt we reset our directory counter and insert.
	if (parentDirectoryString != previousDirectory || previousDirectory == "")
	{
		directoryCounter = 1;
		std::string parentDirectoryKey = parentDirectoryString + "_" + std::to_string(directoryCounter);
		musicBuffer.insert(std::make_pair(parentDirectoryKey, music));
	}
	// Here if the previous directory and parentDirectory passed in are the same we increase the counter by 1 and insert into our unordered map.
	else
	{
		directoryCounter++;
		std::string parentDirectoryKey = parentDirectoryString + "_" + std::to_string(directoryCounter);
		musicBuffer.insert(std::make_pair(parentDirectoryKey, music));
	}
	previousDirectory = parentDirectoryString;
}

void ResourceManager::printMap() {
	for (const auto& [key, value] : textureBuffer) {
		std::cout << key << ": " << &value << std::endl;
	}

	for (const auto& [key, value] : musicBuffer) {
		std::cout << key << ": " << &value << std::endl;
	}


}
