#pragma once
#include <unordered_map>
#include <raylib.h>
#include <string>
#include <filesystem>
#include <iostream>


using namespace std::filesystem;

// NEXT STEP! Optimisations, firstly implementing a destructor for cleanup and learning about move assignments and move operator overloading for efficient resource use.


class ResourceManager
{
public:
	ResourceManager();

	void LoadAllTextures();

	void AddTexture(Texture2D texture, path parentDirectory);

	void printMap();

	template<typename T>
	T GetResource(const std::string& userPrompt);

	

	// We will then iterate through each working directory and then add our resources to our maps.
private:
	std::unordered_map<std::string, Texture2D> textureBuffer;

	path resourcePath = "./res/";

	std::string previousDirectory = "";
	int directoryCounter;
};


