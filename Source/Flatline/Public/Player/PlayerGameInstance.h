// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/TimeStruct.h"
#include "Structs/PlayerStatsStruct.h"
#include "PlayerGameInstance.generated.h"

class UNoteData;
struct FPlayerStatsStruct;

/**
 * Custom game instance to hold persistent player data
 * between levels and sessions.
 */

UCLASS()
class FLATLINE_API UPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPlayerGameInstance();

	/** Notes the player has collected */
	UPROPERTY(BlueprintReadWrite)
	TArray<UNoteData*> Notes;

	/** Player statistics (hunger, thirst, hygiene, etc.) */
	UPROPERTY(BlueprintReadWrite)
	FPlayerStatsStruct PlayerStats;

	/** In-game time & day */
	UPROPERTY(BlueprintReadWrite)
	FTimeStruct TimeStruct;

	/** Currently active quest text */
	UPROPERTY(BlueprintReadWrite)
	FText ActiveQuestText;
	
	/** Set of completed quest IDs */
	UPROPERTY(BlueprintReadWrite)
	TSet<FName> CompletedQuests;

	/** Set of dialogue IDs the player has already seen */
	UPROPERTY(BlueprintReadWrite)
	TSet<FName> SeenDialogues;
	
	/** Save current game data to disk */
	UFUNCTION(BlueprintCallable)
	void SaveGameData();

	/** Load saved game data from disk */
	UFUNCTION(BlueprintCallable)
	bool LoadGameData();

protected:
	virtual void Init() override;
};
