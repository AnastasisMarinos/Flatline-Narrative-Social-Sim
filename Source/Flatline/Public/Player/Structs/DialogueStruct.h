// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "DialogueStruct.generated.h"

/**
 * Struct setting dialogue lines & choices.
 */

USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ChoiceText;

	// If branching: index in DialogueLines array to jump to
	// If -1: just continue to next line
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NextLineIndex = -1;
};

USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MultiLine=true))
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayAfter = 1.5f;

	// Choices appear after this line (optional)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueChoice> Choices;
};
