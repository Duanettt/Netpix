#pragma once
#include <unordered_map>
#include <raylib.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <type_traits>


using namespace std::filesystem;

// NEXT STEP! Optimisations, firstly implementing a destructor for cleanup and learning about move assignments and move operator overloading for efficient resource use.


class ResourceManager
{
public:
	// Delete copy constructor and assignment operator
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	// Public static access method
	static ResourceManager& getInstance() {
		static ResourceManager instance; // Created once and shared
		return instance;
	}

	void LoadAllTextures();

	void AddTexture(Texture2D texture, path parentDirectory);

	void AddMusic(Music music, path parentDirectory);

	void printMap();

	template<typename T>
	T& GetResource(const std::string& userPrompt);

	template<>
	Texture2D& GetResource<Texture2D>(const std::string& userPrompt) {
		auto it = textureBuffer.find(userPrompt);
		if (it != textureBuffer.end()) {
			return it->second;
		}
		else {
			throw std::runtime_error("Texture resource cannot be found: " + userPrompt);
		}
	}

	template<>
	Music& GetResource<Music>(const std::string& userPrompt) {
		auto it = musicBuffer.find(userPrompt);
		if (it != musicBuffer.end()) {
			return it->second;
		}
		else {
			throw std::runtime_error("Music resource cannot be found: " + userPrompt);
		}
	}
	
	// We will then iterate through each working directory and then add our resources to our maps.
private:


	ResourceManager();

	// Private destructor
	~ResourceManager() {
		std::cout << "ResourceManager destroyed. Cleaning up resources...\n";
		for (auto& [key, texture] : textureBuffer) {
			UnloadTexture(texture); // Properly unload textures
		}
	}

	std::unordered_map<std::string, Texture2D> textureBuffer;
	std::unordered_map<std::string, Music> musicBuffer;

	path resourcePath = "./res/";

	std::string previousDirectory = "";
	int directoryCounter;
};


