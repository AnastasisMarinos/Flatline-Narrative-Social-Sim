// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerNotesComponent.generated.h"

class UPlayerGameInstance;
class UNoteData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotesUpdated, const TArray<UNoteData*>&, Notes);

/**
 * Handles the collection and storage of player notes.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FLATLINE_API UPlayerNotesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Broadcast when the notes array changes. */
	UPROPERTY(BlueprintAssignable, Category = "Notes")
	FOnNotesUpdated OnNotesUpdated;

public:
	/** Adds a note to the collection. */
	UFUNCTION(BlueprintCallable, Category = "Notes")
	void AddNote(UNoteData* NewNote);

	/** Returns all notes collected by the player. */
	UFUNCTION(BlueprintCallable, Category = "Notes")
	const TArray<UNoteData*>& GetNotes() const { return Notes; }

protected:
	virtual void BeginPlay() override;

private:
	/** The player's collected notes in the current session. */
	UPROPERTY()
	TArray<UNoteData*> Notes;

	/** Reference to the game instance for persistent note storage. */
	UPROPERTY()
	UPlayerGameInstance* GameInstanceRef = nullptr;
};
