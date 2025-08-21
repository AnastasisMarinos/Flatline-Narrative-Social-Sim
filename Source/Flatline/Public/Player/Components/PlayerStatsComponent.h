// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/PlayerGameInstance.h"
#include "PlayerStatsComponent.generated.h"

class UPlayerGameInstance;

/**
 * Manages the player's survival stats and handles automatic decay over time.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FLATLINE_API UPlayerStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerStatsComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Changes stats by the given delta values and clamps them internally. */
	void ChangeStats(const FPlayerStatsStruct& StatsChange);

	/** Applies stat decay (called on a timer). */
	void DecayStats();

	/** Saves current stats to the game instance. */
	void SaveStatsToGameInstance();

	/** Loads stats from the game instance. */
	void LoadStatsFromGameInstance();

private:
	/** Current player stats during gameplay. */
	UPROPERTY(BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FPlayerStatsStruct PlayerStats;

	/** Per-second decay values for each stat. */
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	FPlayerStatsStruct StatDecay;

	/** Timer handle for automatic stat decay. */
	FTimerHandle StatDecayTimer;

	/** Reference to the persistent game instance. */
	UPROPERTY()
	UPlayerGameInstance* GameInstanceRef = nullptr;
};
