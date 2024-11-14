#pragma once
#include <unordered_map>
#include <raylib.h>
#include <string>
#include <filesystem>
#include <iostream>


using namespace std::filesystem;

class ResourceManager
{
public:
	ResourceManager();

	void LoadAllTextures();

	// We will then iterate through each working directory and then add our resources to our maps.

	template<typename T>
	T GetResource();
private:
	std::unordered_map<std::string, Texture2D*> textureBuffer;

	path resourcePath = "./res/";
};

