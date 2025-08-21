// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteViewWidget.generated.h"

class UTextBlock;
class UNoteData;

UCLASS()
class FLATLINE_API UNoteViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Mail")
	void SetupNote(UNoteData* InNote);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ContentText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SenderText;

	// Optional: close button click
	UFUNCTION(BlueprintCallable)
	void CloseView();
};
