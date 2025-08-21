// (C) Anastasis Marinos 2025 //

#include "Player/PlayerGameInstance.h"
#include "Player/PlayerSaveGame.h"
#include "Kismet/GameplayStatics.h"

UPlayerGameInstance::UPlayerGameInstance()
{
	// Set default player stats when starting a new game
	PlayerStats.Hunger  = 40.f;
	PlayerStats.Thirst  = 40.f;
	PlayerStats.Energy  = 100.f;
	PlayerStats.Hygiene = 60.f;
	PlayerStats.Toilet  = 0.f;
}

void UPlayerGameInstance::Init()
{
	Super::Init();

	// Attempt to load saved data at startup
	LoadGameData();
}

void UPlayerGameInstance::SaveGameData()
{
	// Create a new save game object
	UPlayerSaveGame* SaveGameObj = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	// Copy current data into save object
	SaveGameObj->PlayerStats     = PlayerStats;
	SaveGameObj->TimeStruct      = TimeStruct;
	SaveGameObj->Notes           = Notes;
	SaveGameObj->ActiveQuestText = ActiveQuestText;
	SaveGameObj->CompletedEvents = CompletedQuests;

	// Save to slot
	UGameplayStatics::SaveGameToSlot(SaveGameObj, TEXT("PlayerSave"), 0);
}

bool UPlayerGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSave"), 0))
	{
		// Load save game from slot
		UPlayerSaveGame* Loaded = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSave"), 0));
		if (Loaded)
		{
			// Apply loaded data to game instance
			PlayerStats      = Loaded->PlayerStats;
			TimeStruct       = Loaded->TimeStruct;
			Notes            = Loaded->Notes;
			ActiveQuestText  = Loaded->ActiveQuestText;
			CompletedQuests  = Loaded->CompletedEvents;
			return true;
		}
	}

	// No save data found
	return false;
}
