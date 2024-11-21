#pragma once
#include <queue>
#include "./Core/Camera.h"
#include "./Game/GameObjects.h" 
#include "./Game/Player.h"

class DialogueManager
{
public:
	void EndDialogue();
	void StartDialogue(NPC* npc);

	void SetPlayer(Player* player);
	void Update();

	void Draw(NPC* npc); 

	bool GetIsDialogueActive();

private:
	Player* playerPointer;
	bool isDialogueActive = false;
	std::queue<const char*> dialogueLines;
};

