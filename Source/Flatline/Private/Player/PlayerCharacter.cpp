// (C) Anastasis Marinos 2025 //

#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Interactables/InteractableBase.h"
#include "Player/Components/PlayerStatsComponent.h"
#include "Player/Components/PlayerNotesComponent.h"
#include "Player/Interfaces/InteractableInterface.h"
#include "Player/PlayerCharacterController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Components
	PlayerStats = CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("PlayerStats"));
	NotesComp   = CreateDefaultSubobject<UPlayerNotesComponent>(TEXT("NotesComponent"));
	
	// Character movement setup
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 90.f, 0.f);
	GetCharacterMovement()->MaxAcceleration = 768.f;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::SetCurrentInteractable(AInteractableBase* Interactable)
{
	CurrentInteractable = Interactable;

	// If interactable is valid and supports the interface, display the prompt
	if (CurrentInteractable && CurrentInteractable->Implements<UInteractableInterface>())
	{
		FText Prompt = IInteractableInterface::Execute_GetInteractionPrompt(CurrentInteractable);

		// Tell the controller to show the interaction prompt
		if (APlayerCharacterController* PC = Cast<APlayerCharacterController>(GetController()))
		{
			PC->ShowInteractionPrompt(Prompt);
		}
	}
}

void APlayerCharacter::ClearCurrentInteractable(AInteractableBase* Interactable)
{
	// Only clear if it's the same interactable
	if (CurrentInteractable == Interactable)
	{
		CurrentInteractable = nullptr;

		// Hide the interaction prompt on the UI
		if (APlayerCharacterController* PC = Cast<APlayerCharacterController>(GetController()))
		{
			PC->HideInteractionPrompt();
		}
	}
}

void APlayerCharacter::Interact()
{
	// Execute interaction logic on the interactable
	if (CurrentInteractable && CurrentInteractable->Implements<UInteractableInterface>())
	{
		IInteractableInterface::Execute_Interact(CurrentInteractable, this);
	}
}
