#include "DialogueManager.h"

void DialogueManager::EndDialogue()
{
	if (playerPointer)
	{
		playerPointer->SetIsInteracting(false);
		isDialogueActive = false;
	}

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

	if (playerPointer)
	{
		playerPointer->SetIsInteracting(true);
	}
	isDialogueActive = true;
}

void DialogueManager::SetPlayer(Player* player)
{
	playerPointer = player;
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

void DialogueManager::Draw(NPC* npc)
{
	if (!isDialogueActive) return;

	// Dialogue box screen-space coordinates
	Vector2 dialogueBoxPosition = { 0.0f, 400.0f }; // Position for the dialogue box

	// Fixed NPC screen position for dialogues
	npc->DrawDialogueSprite(5); // Pass scale factor to draw large sprite
	DrawRectangle(dialogueBoxPosition.x, dialogueBoxPosition.y - 50, 400, 400, BLACK); // Draw dialogue box
	if (!dialogueLines.empty())
	{
		DrawText(dialogueLines.front(), dialogueBoxPosition.x + 10, dialogueBoxPosition.y - 50, 20, WHITE);
	}


}

bool DialogueManager::GetIsDialogueActive()
{
	return isDialogueActive;
}



