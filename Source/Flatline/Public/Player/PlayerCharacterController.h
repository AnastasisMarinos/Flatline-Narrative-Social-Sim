// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

struct FDialogueChoice;
// Forward declarations
class UPlayerWidget;
class UInputAction;
class APlayerCharacter;
struct FInputActionValue;

/**
 * Custom player controller for handling:
 * - Enhanced Input binding
 * - UI interaction (inventory, prompts, monologues)
 * - Player pawn possession logic
 */

UCLASS(Abstract)
class FLATLINE_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	// ---------------------------
	// Input Settings
	// ---------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = true))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Movement")
	UInputAction* IA_Sprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Actions")
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Actions")
	UInputAction* IA_Inventory;

	// ---------------------------
	// UI
	// ---------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UPlayerWidget* PlayerWidgetInstance;

	// Player turning state (used for animation/UI)
	UPROPERTY(BlueprintReadOnly)
	bool bIsTurningRight = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsTurningLeft = false;

	// ---------------------------
	// UI Helper Functions
	// ---------------------------
	void ShowInteractionPrompt(const FText& Prompt);
	void HideInteractionPrompt();
	void ShowErrorMessage(const FText& ErrorMessage);
	void BlinkOnInteraction(float BlinkTime);
	void ShowMonologue(const FText& Text);
	void ShowDialogue(const FText& Speaker, const FText& Text);
	void ShowDialogueChoices(const TArray<FDialogueChoice>& Choices);

	UFUNCTION(BlueprintCallable)
	void WidgetChoiceClicked(int32 ChoiceIndex);
	void SetActiveDialogue(class UDialogueComponent* Dialogue);
	void ClearActiveDialogue();
	
	void SetActiveQuestText(const FText& QuestText);
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// Input callbacks
	void OnMove(const FInputActionValue& InputActionValue);
	void OnInteract();
	void OnToggleInventory();
	
private:
	// Cached references
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter = nullptr;

	// Sprint state
	bool bIsSprinting = false;
	
	UPROPERTY()
	class UDialogueComponent* ActiveDialogue = nullptr;
};
