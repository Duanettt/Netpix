#pragma once
#include <queue>
#include "src/Game/GameObjects.h"
#include "src/Core/Camera.h" 

class DialogueManager
{
public:
	void EndDialogue();
	void StartDialogue(NPC* npc);

	void Update();

	void Draw(CameraController& camera);


	bool GetIsDialogueActive();

private:
	bool isDialogueActive = false;
	std::queue<const char*> dialogueLines;
};

