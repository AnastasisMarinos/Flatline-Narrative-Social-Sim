// (C) Anastasis Marinos 2025 //

#include "Player/Components/PlayerNotesComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerGameInstance.h"

void UPlayerNotesComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceRef = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstanceRef)
	{
		Notes = GameInstanceRef->Notes;
	}
}

void UPlayerNotesComponent::AddNote(UNoteData* NewNote)
{
	if (!NewNote || !GameInstanceRef)
	{
		return;
	}

	Notes.Add(NewNote);
	GameInstanceRef->Notes.Add(NewNote);

	OnNotesUpdated.Broadcast(Notes);
}
