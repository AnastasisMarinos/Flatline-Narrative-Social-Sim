// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteButtonWidget.generated.h"

class UNoteData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMailItemClicked, UNoteData*, Note);

UCLASS()
class FLATLINE_API UNoteButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Mail")
	FOnMailItemClicked OnMailItemClicked;

	UFUNCTION(BlueprintCallable)
	void Setup(UNoteData* InNote);

protected:
	UPROPERTY(BlueprintReadOnly, Category="Mail")
	UNoteData* NoteDataRef;

	UFUNCTION(BlueprintCallable, Category="Mail")
	void HandleClick();
};
