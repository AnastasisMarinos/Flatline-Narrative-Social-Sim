// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameMode.generated.h"

/**
 * Custom game mode for the player experience.
 * Sets default pawn and controller classes from Blueprints.
 */

UCLASS()
class FLATLINE_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Constructor
	APlayerGameMode();
};
