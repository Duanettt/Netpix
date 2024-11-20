#include "DialogueManager.h"

void DialogueManager::EndDialogue()
{
	isDialogueActive = false;

}

void DialogueManager::StartDialogue(NPC* npc)
{

	if (isDialogueActive) return;

	std::cout << "About to get dialogue lines" << std::endl;

	// Clear the lines before use.
	dialogueLines = std::queue<const char*>();
	for (const auto& user_DialogueLines : npc->getDialogueLines())
	{
		std::cout << user_DialogueLines << std::endl;
		dialogueLines.push(user_DialogueLines);
	}

	isDialogueActive = true;
}

void DialogueManager::Update()
{
	if (!isDialogueActive) return;

	if (isDialogueActive)
	{
		if (IsKeyPressed(KEY_ENTER) && !dialogueLines.empty())
		{
			dialogueLines.pop();
			if (dialogueLines.empty())
			{
				std::cout << "Ending Dialogue!" << std::endl;
				EndDialogue();
			}
		}

	}
}

void DialogueManager::Draw(CameraController& camera, NPC* npc)
{
	Vector2 npcCharacterScreenPosition = { camera.getCameraPosition().x + 250.0f, camera.getCameraPosition().y};
	if (!isDialogueActive) return;
	DrawRectangle(camera.getCameraPosition().x + 250.0f, camera.getCameraPosition().y, 400, 200, BLACK); // Dialogue box
	if (!dialogueLines.empty()) {
		npc->DrawObject(camera, npcCharacterScreenPosition, 1);
		DrawText(dialogueLines.front(), camera.getCameraPosition().x + 250.0f, camera.getCameraPosition().y, 20, WHITE);
	}
}


bool DialogueManager::GetIsDialogueActive()
{
	return isDialogueActive;
}



