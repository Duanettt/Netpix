#include "../Scene.h"

void Scene::AddComponentPointerToSceneVector(SceneComponent* component)
{
    components.push_back(component);
}

void Scene::AddGameObjectPointerToSceneVector(GameObjects* object)
{
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
        if (npc != nullptr)
        {
            npcVec.push_back(npc);
        }
    }
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

void Scene::DrawScene(Player& player, CameraController& camera) const
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
    }
    player.Draw();

    camera.EndCameraMode();
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

    this->checkCollisions(player);
}

void Scene::Unload()
{
    for (auto& component : components)
    {
        component->Unload();
    }

    components.clear();
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
    for (const auto& object : objects)
    {
        NPC* npc = dynamic_cast<NPC*>(object);
        if (npc != nullptr)
        {
            if (CheckCollisionRecs(npc->GetCurrentObjectBoundingRect(), playerRect))
            {
                DrawRectangle(player.GetPlayerPosition().x, player.GetPlayerPosition().y, playerRect.width, playerRect.height, RED);
                return true;
            }
        }
    }
    return false;
}
