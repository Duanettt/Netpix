#include "DialogueManager.h"

void DialogueManager::EndDialogue()
{
	isDialogueActive = false;

}

void DialogueManager::StartDialogue(NPC* npc)
{
	std::cout << "About to get dialogue lines" << std::endl;
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
		std::cout << "Updating our dialogue!" << std::endl;
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

void DialogueManager::Draw(CameraController& camera)
{
	if (!isDialogueActive) return;
	DrawRectangle(camera.getCameraPosition().x + 105.0f, camera.getCameraPosition().y, 200, 300, BLACK); // Dialogue box
	if (!dialogueLines.empty()) {
		DrawText(dialogueLines.front(), camera.getCameraPosition().x + 105.0f, camera.getCameraPosition().y, 20, WHITE);
	}
}


bool DialogueManager::GetIsDialogueActive()
{
	return isDialogueActive;
}



