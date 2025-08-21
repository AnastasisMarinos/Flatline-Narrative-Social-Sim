// (C) Anastasis Marinos 2025 //

#include "Player/Components/DialogueComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/Data/DialogueData.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerCharacterController.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}

void UDialogueComponent::StartDialogue(int32 StartLineIndex /*=0*/)
{
	if (DialogueAsset)
	{
		DialogueLines = DialogueAsset->DialogueLines; // Copy from asset
	}

	if (DialogueLines.Num() == 0 || StartLineIndex < 0 || StartLineIndex >= DialogueLines.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid dialogue start on %s"), *GetOwner()->GetName());
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(AdvanceTimer);
	bIsRunning = true;
	CurrentLineIndex = StartLineIndex;

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetActiveDialogue(this);
	}

	PlayCurrentLine();
}

void UDialogueComponent::EndDialogue()
{
	if (!bIsRunning) return;

	GetWorld()->GetTimerManager().ClearTimer(AdvanceTimer);
	bIsRunning = false;
	CurrentLineIndex = INDEX_NONE;

	// Optional: ask UI to clear dialogue/choices
	if (PlayerControllerRef)
	{
		PlayerControllerRef->ShowDialogue(FText::GetEmpty(), FText::GetEmpty());
		// If you add a HideDialogueChoices() BP event on UPlayerWidget,
		// call it via controller here. For now, sending empty choices is fine:
		PlayerControllerRef->ShowDialogueChoices(TArray<FDialogueChoice>{});
		PlayerControllerRef->ClearActiveDialogue();
	}
}

void UDialogueComponent::PlayCurrentLine()
{
	if (!bIsRunning || CurrentLineIndex < 0 || CurrentLineIndex >= DialogueLines.Num())
	{
		EndDialogue();
		return;
	}

	const FDialogueLine& Line = DialogueLines[CurrentLineIndex];
	
	// Show the line
	if (PlayerControllerRef)
	{
		PlayerControllerRef->ShowDialogue(Line.SpeakerName, Line.DialogueText);
	}

	// If there are choices after this line, show them after DelayAfter
	if (Line.Choices.Num() > 0)
	{
		const float Delay = FMath::Max(0.f, Line.DelayAfter);
		if (Delay > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(AdvanceTimer, this, &UDialogueComponent::ShowChoices, Delay, false);
		}
		else
		{
			ShowChoices();
		}
	}
	else
	{
		// No choices: auto-advance after DelayAfter
		const float Delay = FMath::Max(0.f, Line.DelayAfter);
		if (Delay > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(AdvanceTimer, this, &UDialogueComponent::AdvanceToNextLine, Delay, false);
		}
		else
		{
			AdvanceToNextLine();
		}
	}
}

void UDialogueComponent::ShowChoices()
{
	if (!bIsRunning || CurrentLineIndex < 0 || CurrentLineIndex >= DialogueLines.Num())
	{
		EndDialogue();
		return;
	}

	const FDialogueLine& Line = DialogueLines[CurrentLineIndex];

	if (Line.Choices.Num() == 0)
	{
		// Nothing to show; just advance (safety)
		AdvanceToNextLine();
		return;
	}

	// Push choices to UI
	// Show the line
	if (PlayerControllerRef)
	{
		PlayerControllerRef->ShowDialogueChoices(Line.Choices);
	}

}

void UDialogueComponent::SelectChoice(int32 ChoiceIndex)
{
	if (!bIsRunning || CurrentLineIndex < 0 || CurrentLineIndex >= DialogueLines.Num())
	{
		return;
	}

	const FDialogueLine& Line = DialogueLines[CurrentLineIndex];

	if (!Line.Choices.IsValidIndex(ChoiceIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectChoice: invalid index %d on %s"), ChoiceIndex, *GetOwner()->GetName());
		return;
	}

	// Stop any pending timers (we're moving now)
	GetWorld()->GetTimerManager().ClearTimer(AdvanceTimer);

	const FDialogueChoice& Choice = Line.Choices[ChoiceIndex];
	const int32 NextIdx = (Choice.NextLineIndex >= 0) ? Choice.NextLineIndex : (CurrentLineIndex + 1);

	if (NextIdx < 0 || NextIdx >= DialogueLines.Num())
	{
		// If branch points outside the script, just end gracefully
		EndDialogue();
		return;
	}

	CurrentLineIndex = NextIdx;
	PlayCurrentLine();
}

void UDialogueComponent::AdvanceToNextLine()
{
	if (!bIsRunning)
		return;

	++CurrentLineIndex;

	if (CurrentLineIndex >= DialogueLines.Num())
	{
		EndDialogue();
		return;
	}

	PlayCurrentLine();
}