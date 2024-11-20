#pragma once
#include <queue>
#include "./Core/Camera.h"
#include "./Game/GameObjects.h" 

class DialogueManager
{
public:
	void EndDialogue();
	void StartDialogue(NPC* npc);

	void Update();

	void Draw(CameraController& camera, NPC* npc); 

	bool GetIsDialogueActive();

private:
	bool isDialogueActive = false;
	std::queue<const char*> dialogueLines;
};

