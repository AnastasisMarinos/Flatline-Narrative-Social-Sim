// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatsStruct.generated.h"

/**
 * Struct for tracking the player's survival-related stats.
 */

USTRUCT(BlueprintType)
struct FPlayerStatsStruct
{
	GENERATED_BODY()

	/** Hunger level (0 = starving, 100 = full) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Hunger = 100.f;

	/** Thirst level (0 = dehydrated, 100 = fully hydrated) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Thirst = 100.f;

	/** Energy level (0 = exhausted, 100 = fully rested) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Energy = 100.f;

	/** Toilet need level (0 = empty, 100 = urgent) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Toilet = 0.f;

	/** Hygiene level (0 = filthy, 100 = perfectly clean) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	float Hygiene = 100.f;

	/**
	 * Clamps all stats to a valid range [0, 100].
	 * Useful after calculations to avoid out-of-bound values.
	 */
	void ClampStats()
	{
		Hunger  = FMath::Clamp(Hunger,  0.f, 100.f);
		Thirst  = FMath::Clamp(Thirst,  0.f, 100.f);
		Energy  = FMath::Clamp(Energy,  0.f, 100.f);
		Toilet  = FMath::Clamp(Toilet,  0.f, 100.f);
		Hygiene = FMath::Clamp(Hygiene, 0.f, 100.f);
	}
};
