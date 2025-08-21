// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Player/Structs/DialogueStruct.h"
#include "DialogueData.generated.h"

/**
 * Asset that stores a full dialogue script.
 * You can create these in the Content Browser and assign to a DialogueComponent.
 */
UCLASS(BlueprintType)
class FLATLINE_API UDialogueData : public UDataAsset
{
	GENERATED_BODY()

public:
	/** The lines for this dialogue */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<FDialogueLine> DialogueLines;
};