// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NoteData.generated.h"

/**
 * Represents a single note that the player can collect.
 */
UCLASS(BlueprintType)
class FLATLINE_API UNoteData : public UDataAsset
{
	GENERATED_BODY()

public:
	/** The note's title. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
	FText NoteTitle;

	/** The main body text of the note. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
	FText NoteContent;

	/** Who sent/wrote the note. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
	FText NoteSender;
};
