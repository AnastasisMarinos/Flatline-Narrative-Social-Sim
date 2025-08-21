// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

/**
 * Interface for any object that can be interacted with by the player.
 * Allows for standardized interaction and UI prompt retrieval.
 */

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class FLATLINE_API IInteractableInterface
{
	GENERATED_BODY()

public:
	/**
	 * Triggered when the player interacts with this object.
	 * @param Player - The player character initiating the interaction.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(class APlayerCharacter* Player);

	/**
	 * Returns the text prompt to display in the UI when the player can interact.
	 * Example: "Press [E] to Open Door"
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	FText GetInteractionPrompt() const;
};
