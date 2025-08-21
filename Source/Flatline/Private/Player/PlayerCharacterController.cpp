// (C) Anastasis Marinos 2025 //

#include "Player/PlayerCharacterController.h"
#include "Player/PlayerCharacter.h"
#include "Player/Components/PlayerNotesComponent.h"
#include "UI/PlayerWidget.h"
#include "Player/Components/DialogueComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"

void APlayerCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Cache pawn reference
	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	checkf(PlayerCharacter, TEXT("APlayerCharacterController should only possess APlayerCharacter pawns."));

	// Get input component
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to EnhancedInputComponent."));

	// Get local player input subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to EnhancedInputLocalPlayerSubsystem."));

	// Apply mapping context
	checkf(DefaultMappingContext, TEXT("InputMappingContext was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);

	// Bind input actions
	if (IA_Move)     EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnMove);
	if (IA_Interact) EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &APlayerCharacterController::OnInteract);
	if (IA_Inventory)EnhancedInputComponent->BindAction(IA_Inventory, ETriggerEvent::Started, this, &APlayerCharacterController::OnToggleInventory);

	// Create and show player widget
	if (PlayerWidgetClass)
	{
		PlayerWidgetInstance = CreateWidget<UPlayerWidget>(this, PlayerWidgetClass);
		if (PlayerWidgetInstance)
		{
			PlayerWidgetInstance->AddToViewport();
			PlayerWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}

	// Bind note updates to UI
	if (PlayerCharacter && PlayerCharacter->NotesComp && PlayerWidgetInstance)
	{
		PlayerCharacter->NotesComp->OnNotesUpdated.AddDynamic(PlayerWidgetInstance, &UPlayerWidget::RefreshMailList);

		// Populate with initial notes
		PlayerWidgetInstance->RefreshMailList(PlayerCharacter->NotesComp->GetNotes());
	}
}

void APlayerCharacterController::OnUnPossess()
{
	// Clear input bindings
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionBindings();
	}
	
	Super::OnUnPossess();
}

void APlayerCharacterController::OnMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// Move forward/back
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);

	// Track turn direction for animation/UI
	if (MovementVector.X == 0.0f)
	{
		bIsTurningRight = false;
		bIsTurningLeft  = false;
	}
	else if (MovementVector.X > 0.0f) bIsTurningRight = true;
	else if (MovementVector.X < 0.0f) bIsTurningLeft  = true;
	
	// Apply rotation
	AddYawInput(MovementVector.X * 2.8f);
}

void APlayerCharacterController::OnInteract()
{
	PlayerCharacter->Interact();
}

void APlayerCharacterController::OnToggleInventory()
{
	if (!PlayerWidgetInstance || !PlayerCharacter || !PlayerCharacter->NotesComp) return;

	PlayerWidgetInstance->ToggleInventory();
	PlayerWidgetInstance->RefreshMailList(PlayerCharacter->NotesComp->GetNotes());
}

// ---------------------------
// UI Helper Functions
// ---------------------------
void APlayerCharacterController::ShowInteractionPrompt(const FText& Prompt)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->ShowInteractionPrompt(Prompt);
}

void APlayerCharacterController::HideInteractionPrompt()
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->HideInteractionPrompt();
}

void APlayerCharacterController::ShowErrorMessage(const FText& ErrorMessage)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->ShowErrorMessage(ErrorMessage);
}

void APlayerCharacterController::BlinkOnInteraction(float BlinkTime)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->BlinkOnInteraction(BlinkTime);
}

void APlayerCharacterController::ShowMonologue(const FText& Text)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->ShowMonologue(Text);
}

void APlayerCharacterController::ShowDialogue(const FText& Speaker, const FText& Text)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->ShowDialogue(Speaker, Text);
}

void APlayerCharacterController::ShowDialogueChoices(const TArray<FDialogueChoice>& Choices)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->ShowDialogueChoices(Choices);
}

void APlayerCharacterController::WidgetChoiceClicked(int32 ChoiceIndex)
{
	if (ActiveDialogue)
	{
		ActiveDialogue->SelectChoice(ChoiceIndex);
		PlayerWidgetInstance->ClearDialogueChoices();
	}
}

void APlayerCharacterController::SetActiveDialogue(UDialogueComponent* Dialogue)
{
	ActiveDialogue = Dialogue;
}

void APlayerCharacterController::ClearActiveDialogue()
{
	ActiveDialogue = nullptr;
}

void APlayerCharacterController::SetActiveQuestText(const FText& QuestText)
{
	if (PlayerWidgetInstance)
		PlayerWidgetInstance->SetActiveQuestText(QuestText);
}
