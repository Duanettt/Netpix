#include "../Scene.h"

void Scene::AddComponentPointerToSceneVector(SceneComponent* component)
{
    components.push_back(component);
}

void Scene::AddGameObjectPointerToSceneVector(GameObjects* object)
{
    std::cout << "The memory address for the object pointer is: " << object << std::endl;
    objects.push_back(object);
}

void Scene::AddMusicPointerToMusicMap(std::string musicName, MusicComponent* music)
{
    musicMap[musicName] = music;
}

NPC* Scene::getNPC()
{
    for (const auto& object : objects)
    {
        NPC* npc = dynamic_cast<NPC*>(object);
        if (npc != nullptr)
        {
            return npc;
        }
    }
    return nullptr;
}

NPC* Scene::getNPCByIndex(int num)
{
    std::vector<NPC*> npcVec;

    for (const auto& object : objects)
    {
        NPC* npc = dynamic_cast<NPC*>(object);
        std::cout << "The memory address when we get the NPC by index is: " << npc << std::endl;
        if (npc != nullptr)
        {
            npcVec.push_back(npc);
            std::cout << "This NPC's memory address is: " << npc << std::endl;
        }
    }

    std::cout << "The memory address we're about to return" << npcVec[num] << std::endl;
    return npcVec[num];
}

float Scene::getWorldWidth()
{
    for (const auto& component : components)
    {
        Foreground* fg = dynamic_cast<Foreground*>(component);
        if (fg != nullptr)
        {
            return fg->getTexture().width * 2;
        }
    }
    return 0.0f;
}

float Scene::getWorldHeight()
{
    for (const auto& component : components)
    {
        Foreground* fg = dynamic_cast<Foreground*>(component);
        if (fg != nullptr)
        {
            return fg->getTexture().height * 2;
        }
    }
    return 0.0f;
}

void Scene::DrawScene(Player& player, CameraController& camera)
{
    currentMusic->PlayMusic();

    camera.BeginCameraMode();

    for (const auto& component : components)
    {
        component->Draw(camera);
    }

    for (const auto& object : objects)
    {
        object->DrawObject(camera);

        if (object == player.GetActiveObject())
        {
            DrawRectangleLinesEx(object->GetCurrentObjectBoundingRect(), 2.0f, YELLOW);
            DrawText("Press 'E' to Interact", player.GetPlayerPosition().x, player.GetPlayerPosition().y, 20, RED);
        }
    }

    player.Draw();

    //FIXME: Might decouple the camera from this class and move it one up for the scene manager to allow to manage between UI and Game Objects.  

    camera.EndCameraMode();

    dm.Draw(dynamic_cast<NPC*>(closestObject));

}

void Scene::UpdateScene(Player& player, CameraController& camera)
{
    currentMusic->UpdateMusic();

    camera.UpdateCamera(player.GetPlayerPosition(), this->getWorldWidth(), this->getWorldHeight());

    for (const auto& component : components)
    {
        component->Update(camera);
    }

    for (const auto& object : objects)
    {
        object->UpdateObject();
    }

    player.Update(this->getWorldWidth());

    // Might move this into scenemanager to check for collisions to allow us.
    collisionDetected = this->checkCollisions(player);

    if (collisionDetected && player.IsInteracting() && player.GetActiveObject())
    {
        if (closestObject)
            // Dynamic casting is very bad for performance to much.. we need to start implementing ENUMS with object types soon.
            dm.StartDialogue(dynamic_cast<NPC*>(closestObject));

    }

    dm.SetPlayer(&player);
    dm.Update();
}

void Scene::Unload()
{
    for (auto& component : components)
    {
        component->Unload();
    }

    components.clear();

    for (auto& object : objects)
    {
        object->Unload();
    }

    objects.clear();

    for (auto& pair : musicMap) {
        delete pair.second;  // Delete the pointer to MusicComponent
    }
    musicMap.clear();  // Clear the map after deleting the pointers

    if (currentMusic != nullptr) {
        delete currentMusic;
        currentMusic = nullptr;  // Set to nullptr to avoid dangling pointers
    }

    if (closestObject != nullptr) {
        delete closestObject;
        closestObject = nullptr;  // Set to nullptr to avoid dangling pointers
    }



}
    
void Scene::setCurrentSong(std::string musicName)
{
    auto it = musicMap.find(musicName);
    if (it != musicMap.end())
    {
        currentMusic = it->second;
        std::cout << it->first;
        currentMusic->PlayMusic();
    }
    else
    {
        TraceLog(LOG_ERROR, "Current song chosen is not compatible with this scene!");
    }
}

bool Scene::checkCollisions(Player& player)
{
    Rectangle playerRect = player.GetPlayerBoundingRect();
    float closestDistance = FLT_MAX;

    for (const auto& object : objects)
    {
        NPC* npc = dynamic_cast<NPC*>(object);
        if (npc != nullptr)
        {
            if (CheckCollisionRecs(npc->GetCurrentObjectBoundingRect(), playerRect))
            {

                float distance = Vector2Distance(player.GetPlayerPosition(), object->cameraAdjustedPosition);

                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestObject = object;
                    std::cout << closestDistance << std::endl;
                }
                // If this returns true we set a variable to true and draw our rectangle.
                // Collision detection somewhat working for each scene. So now 

                player.SetActiveObject(closestObject);
                std::cout << "Collision detected!" << std::endl;
                return true;
            }
        }
    }

    player.SetActiveObject(nullptr);
    return false;
}

SceneComponent::SceneComponent(const char* filePath)
{
    texture = LoadTexture(filePath);
    if (texture.width == 0 || texture.height == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
    }
}

SceneComponent::SceneComponent(std::string textureKey)
{
    texture = ResourceManager::getInstance().GetResource<Texture2D>(textureKey);
    if (texture.width == 0 || texture.height == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", textureKey);
    }
}

int SceneComponent::getWidth()
{
    return this->getTexture().width;
}

int SceneComponent::getHeight()
{
    return this->getTexture().height;
}
