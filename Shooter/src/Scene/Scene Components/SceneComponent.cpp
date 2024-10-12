#include "../Scene.h"
#include <iostream>

Texture2D SceneComponent::getTexture()
{
    return texture;
}

SceneComponent::~SceneComponent()
{
    // Default destructor implementation
}
