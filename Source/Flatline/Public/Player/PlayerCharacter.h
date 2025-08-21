// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

// Forward declarations
class UPlayerNotesComponent;
class UPlayerStatsComponent;
class AInteractableBase;

/**
 * Player-controlled character.
 * Handles movement, stats, notes collection, and interacting with the world.
 */

UCLASS()
class FLATLINE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Constructor
	APlayerCharacter();

	/** Player stats (hunger, thirst, etc.) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	UPlayerStatsComponent* PlayerStats;

	/** Notes system for storing collected notes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Notes")
	UPlayerNotesComponent* NotesComp;

	/** Accessor for player stats */
	UPlayerStatsComponent* GetPlayerStats() const { return PlayerStats; }
	
	/** Attempts to interact with the currently targeted object */
	void Interact();

	/** Sets the current interactable actor */
	void SetCurrentInteractable(AInteractableBase* Interactable);

	/** Clears the current interactable actor */
	void ClearCurrentInteractable(AInteractableBase* Interactable);

protected:
	virtual void BeginPlay() override;

private:
	/** The interactable actor the player is currently looking at / near */
	UPROPERTY()
	AInteractableBase* CurrentInteractable;
};
