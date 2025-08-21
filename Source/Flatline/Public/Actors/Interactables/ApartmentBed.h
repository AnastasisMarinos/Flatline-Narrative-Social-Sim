#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/ConsumableBase.h"
#include "ApartmentBed.generated.h"

class UPlayerGameInstance;
class ATimeManager;

UCLASS()
class FLATLINE_API AApartmentBed : public AConsumableActor
{
	GENERATED_BODY()

public:
	AApartmentBed();

	virtual void Interact_Implementation(class APlayerCharacter* Player) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATimeManager* TimeManagerRef = nullptr;

	UPROPERTY()
	UPlayerGameInstance* GameInstanceRef = nullptr;
};
