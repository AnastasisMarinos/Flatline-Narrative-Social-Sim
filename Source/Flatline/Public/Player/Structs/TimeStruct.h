// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "TimeStruct.generated.h"

/**
 * Struct representing in-game time and date.
 */

USTRUCT(BlueprintType)
struct FTimeStruct
{
	GENERATED_BODY()
	
	/** Current day (1-based) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 Day = 5;

	/** Current month (1-based) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 Month = 11;

	/** Current hour (0-23) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 Hour = 10;

	/** Current minute (0-59) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 Minute = 0;
};
