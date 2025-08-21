// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestData.generated.h"

/**
 * A single line of quest-related dialogue/monologue.
 */
USTRUCT(BlueprintType)
struct FQuestMonologue
{
	GENERATED_BODY()
	
	/** The dialogue text. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monologue")
	FText LineText;

	/** Delay before showing the next line (in seconds). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monologue")
	float LineDelay = 1.5f;
};

/**
 * Contains quest text and associated monologue lines.
 */
UCLASS(BlueprintType)
class FLATLINE_API UQuestData : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Unique identifier for this quest. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	/** The quest text shown when active. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FText ActiveQuestText;

	/** Optional monologue lines for this quest. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestMonologue> QuestMonologue;
};
