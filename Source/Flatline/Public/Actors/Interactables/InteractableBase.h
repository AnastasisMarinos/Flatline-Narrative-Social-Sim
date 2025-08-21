// (C) Anastasis Marinos 2025
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/Interfaces/InteractableInterface.h"
#include "Sound/SoundBase.h"
#include "InteractableBase.generated.h"

class UBoxComponent;
class APlayerCharacter;

UCLASS()
class FLATLINE_API AInteractableBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* InteractionBox;

	// Interaction properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bCanInteract = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionErrorMessage = FText::FromString("Can't interact right now.");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionPrompt = FText::FromString("Press [Space] to interact");

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float BlinkTime = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Sound")
	USoundBase* InteractionSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap events
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Interface implementations
	virtual void Interact_Implementation(APlayerCharacter* Player) override;
	virtual FText GetInteractionPrompt_Implementation() const override { return InteractionPrompt; }
};
