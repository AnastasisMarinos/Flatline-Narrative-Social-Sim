// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

struct FDialogueChoice;
class UVerticalBox;
class UNoteData;
class UNoteButtonWidget;

UCLASS()
class FLATLINE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Displays prompt text like "Press [Space] to interact"
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ShowInteractionPrompt(const FText& PromptText);

	// Clears interaction prompt
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void HideInteractionPrompt();

	// Called when interaction fails
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ShowErrorMessage(const FText& ErrorMessage);

	// Called when interaction succeeds
	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void BlinkOnInteraction(float BlinkTime);

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ToggleInventory();

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ShowMonologue(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ShowDialogue(const FText& Speaker, const FText& Text);

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ShowDialogueChoices(const TArray<FDialogueChoice>& Choices);

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void ClearDialogueChoices();

	UFUNCTION(BlueprintCallable)
	void RefreshMailList(const TArray<UNoteData*>& Notes);

	UFUNCTION(BlueprintCallable)
	void ShowNoteDetails(UNoteData* Note);

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void SetActiveQuestText(const FText& QuestText);

protected:
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* MailScrollBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* NoteContentBox;

	UPROPERTY(EditAnywhere, Category="Mail")
	TSubclassOf<UNoteButtonWidget> MailItemWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="Mail")
	TSubclassOf<class UNoteViewWidget> NoteViewWidgetClass;
};
