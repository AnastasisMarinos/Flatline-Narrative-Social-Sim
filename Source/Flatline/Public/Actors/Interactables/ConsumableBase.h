// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/InteractableBase.h"
#include "Player/Structs/PlayerStatsStruct.h"
#include "ConsumableBase.generated.h"

struct FPlayerStatsStruct;

UCLASS()
class FLATLINE_API AConsumableActor : public AInteractableBase
{
	GENERATED_BODY()

public:
	AConsumableActor();

	UFUNCTION(BlueprintCallable)
	void ResetAmountOfUses() {CurrentAmountOfUses = MaxAmountOfUses; }

protected:
	// Editable sliders for each stat effect
	UPROPERTY(EditAnywhere, Category = "Consumable Stats")
	int MaxAmountOfUses = 2;

	UPROPERTY(EditAnywhere, Category = "Consumable Stats")
	int CurrentAmountOfUses = 0;

	// Editable sliders for each stat effect
	UPROPERTY(EditAnywhere, Category = "Interaction|Stats")
	FPlayerStatsStruct PlayerStatsChange;

public:
	// Override interaction behavior
	virtual void Interact_Implementation(class APlayerCharacter* Player) override;
};
