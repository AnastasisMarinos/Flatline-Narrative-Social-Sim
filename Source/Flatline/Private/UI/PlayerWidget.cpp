// (C) Anastasis Marinos 2025 //

#include "UI/PlayerWidget.h"

#include "UI/NoteButtonWidget.h"
#include "Player/Data/NoteData.h"
#include "Components/ScrollBox.h"
#include "UI/NoteViewWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"

void UPlayerWidget::RefreshMailList(const TArray<UNoteData*>& Notes)
{
	if (!MailScrollBox || !MailItemWidgetClass) return;

	MailScrollBox->ClearChildren();

	for (UNoteData* Note : Notes)
	{
		if (!Note) continue;

		UNoteButtonWidget* Item = CreateWidget<UNoteButtonWidget>(this, MailItemWidgetClass);
		if (Item)
		{
			Item->Setup(Note);
			Item->OnMailItemClicked.AddDynamic(this, &UPlayerWidget::ShowNoteDetails);
			MailScrollBox->AddChild(Item);
		}
	}
}

void UPlayerWidget::ShowNoteDetails(UNoteData* Note)
{
	if (!Note || !NoteViewWidgetClass) return;

	UNoteViewWidget* NoteView = CreateWidget<UNoteViewWidget>(this, NoteViewWidgetClass);
	if (NoteView)
	{
		NoteView->SetupNote(Note);
		NoteContentBox->ClearChildren();
		NoteContentBox->AddChildToVerticalBox(NoteView);
	}
}
