#include "Actors/Managers/QuestManager.h"
#include "Player/Data/QuestData.h"
#include "Player/PlayerCharacterController.h"
#include "Player/PlayerGameInstance.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AQuestManager::AQuestManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerControllerRef = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	GameInstanceRef = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetActiveQuestText(GameInstanceRef->ActiveQuestText);
	}
}

void AQuestManager::TriggerQuestByID(FName QuestID)
{
	if (!GameInstanceRef)
		return;

	// Prevent retrigger if already completed
	if (GameInstanceRef->CompletedQuests.Contains(QuestID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest %s already completed."), *QuestID.ToString());
		return;
	}

	for (UQuestData* Quest : AllQuests)
	{
		if (Quest && Quest->QuestID == QuestID)
		{
			if (PlayerControllerRef)
			{
				PlayerControllerRef->SetActiveQuestText(Quest->ActiveQuestText);
				GameInstanceRef->ActiveQuestText = Quest->ActiveQuestText;
			}

			StartQuest(Quest);
			GameInstanceRef->CompletedQuests.Add(QuestID); // Mark as done
			return;
		}
	}
}

void AQuestManager::StartQuest(UQuestData* Quest)
{
	CurrentQuest = Quest;
	CurrentLineIndex = 0;
	PlayNextLine();
}

void AQuestManager::PlayNextLine()
{
	if (!CurrentQuest || !PlayerControllerRef) return;

	if (CurrentLineIndex >= CurrentQuest->QuestMonologue.Num())
	{
		// Clear dialogue after delay of last line
		float LastLineDelay = 2.0f; // fallback delay if no last line

		if (CurrentQuest->QuestMonologue.Num() > 0)
		{
			LastLineDelay = CurrentQuest->QuestMonologue.Last().LineDelay;
		}

		// Set timer to clear dialogue
		GetWorld()->GetTimerManager().SetTimer(LineTimer, [this]()
		{
			if (PlayerControllerRef)
			{
				PlayerControllerRef->ShowMonologue(FText::GetEmpty());
			}
			CurrentQuest = nullptr;
		}, LastLineDelay, false);

		return; // exit now
	}

	const FQuestMonologue& Line = CurrentQuest->QuestMonologue[CurrentLineIndex];

	// Send line to widget
	PlayerControllerRef->ShowMonologue(Line.LineText);

	CurrentLineIndex++;

	// Wait before showing next line
	GetWorld()->GetTimerManager().SetTimer(LineTimer, this, &AQuestManager::PlayNextLine, Line.LineDelay, false);
}

