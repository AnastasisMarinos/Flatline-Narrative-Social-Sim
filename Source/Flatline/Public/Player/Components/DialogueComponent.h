// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/Structs/DialogueStruct.h"
#include "DialogueComponent.generated.h"

class UDialogueData;
class APlayerCharacterController;

/**
 * A reusable, data-driven dialogue component that can be attached to any Actor.
 * Configure DialogueLines in the component; call StartDialogue() to run it.
 * Subscribe your UI to OnDialogueLine/OnDialogueChoices/OnDialogueEnded.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	/** The entire dialogue script for this actor. Edited per-instance. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialogue")
	TArray<FDialogueLine> DialogueLines;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UDialogueData* DialogueAsset;

	/** Start this dialogue (optionally from a specific line). */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void StartDialogue(int32 StartLineIndex = 0);

	/** Select a choice index from the *current* line's choices. */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void SelectChoice(int32 ChoiceIndex);

	/** Force end the dialogue immediately (clears timers, broadcasts ended). */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void EndDialogue();

	/** Is the dialogue currently playing? */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	bool IsRunning() const { return bIsRunning; }

	/** Current line index (valid only when running). */
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	int32 GetCurrentLineIndex() const { return CurrentLineIndex; }

protected:
	virtual void BeginPlay() override;

private:
	void PlayCurrentLine();
	void AdvanceToNextLine();
	void ShowChoices();

private:
	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY()
	int32 CurrentLineIndex = INDEX_NONE;

	FTimerHandle AdvanceTimer;

	UPROPERTY()
	APlayerCharacterController* PlayerControllerRef;
};