// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Data/NoteData.h"
#include "GameFramework/SaveGame.h"
#include "Player/Structs/PlayerStatsStruct.h"
#include "Player/Structs/TimeStruct.h"
#include "PlayerSaveGame.generated.h"

/**
 * Save game container for storing persistent player data.
 * This class holds all the necessary state for saving/loading a game session.
 */

UCLASS()
class FLATLINE_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/** Player stats (hunger, thirst, hygiene, etc.) */
	UPROPERTY(BlueprintReadWrite)
	FPlayerStatsStruct PlayerStats;

	/** Current in-game time & date */
	UPROPERTY(BlueprintReadWrite)
	FTimeStruct TimeStruct;

	/** All notes the player has collected */
	UPROPERTY(BlueprintReadWrite)
	TArray<UNoteData*> Notes;

	/** Currently active quest description */
	UPROPERTY(BlueprintReadWrite)
	FText ActiveQuestText;

	/** Set of completed events/quests */
	UPROPERTY(BlueprintReadWrite)
	TSet<FName> CompletedEvents;
};
