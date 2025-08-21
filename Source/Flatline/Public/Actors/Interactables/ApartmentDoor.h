// ApartmentDoor.h
#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/InteractableBase.h"
#include "ApartmentDoor.generated.h"

class UNoteData;

UCLASS()
class FLATLINE_API AApartmentDoor : public AInteractableBase
{
	GENERATED_BODY()

public:
	AApartmentDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Sound")
	USoundBase* LevelTravelSound;

	// Level to load when opening door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FName LevelTravelName;

	// Mail that can be collected (can store multiple notes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	TArray<UNoteData*> MailNotes;

	virtual void Interact_Implementation(APlayerCharacter* Player) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

protected:
	void GiveMailToPlayer(APlayerCharacter* Player);
	void TravelToCorridor();
};