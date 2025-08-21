// (C) Anastasis Marinos 2025 //

#include "UI/NoteButtonWidget.h"

void UNoteButtonWidget::Setup(UNoteData* InNote)
{
	NoteDataRef = InNote;
}

void UNoteButtonWidget::HandleClick()
{
	OnMailItemClicked.Broadcast(NoteDataRef);
}
