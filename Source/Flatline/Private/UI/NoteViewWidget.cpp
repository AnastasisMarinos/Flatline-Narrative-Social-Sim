// (C) Anastasis Marinos 2025 //

#include "UI/NoteViewWidget.h"
#include "Player/Data/NoteData.h"
#include "Components/TextBlock.h"

void UNoteViewWidget::SetupNote(UNoteData* InNote)
{
	if (!InNote) return;

	if (TitleText)
		TitleText->SetText(InNote->NoteTitle);

	if (ContentText)
		ContentText->SetText(InNote->NoteContent);

	if (SenderText)
		SenderText->SetText(InNote->NoteSender);
}

void UNoteViewWidget::CloseView()
{
	RemoveFromParent();
}
