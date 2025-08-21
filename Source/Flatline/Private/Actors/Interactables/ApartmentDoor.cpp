#include "Actors/Interactables/ApartmentDoor.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Components/PlayerNotesComponent.h"
#include "Player/PlayerCharacterController.h"

AApartmentDoor::AApartmentDoor()
{
	InteractionPrompt = FText::FromString("Press [Space] to interact with door");
}

void AApartmentDoor::Interact_Implementation(APlayerCharacter* Player)
{
	if (!Player) return;

	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Player->GetController());
	if (!PlayerController)
		return;

	if (MailNotes.Num() > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractionSound);
		
		GiveMailToPlayer(Player);
		MailNotes.Empty();
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelTravelSound);
		
		TravelToCorridor();
	}

	// Notify UI of successful interaction via PlayerController
	PlayerController->BlinkOnInteraction(BlinkTime);
	
	Player->SetCurrentInteractable(this);
}

FText AApartmentDoor::GetInteractionPrompt_Implementation() const
{
	if (MailNotes.Num() > 0)
	{
		return FText::FromString("Press [Space] to collect mail");
	}
	else
	{
		return FText::FromString("Press [Space] to exit");
	}
}

void AApartmentDoor::GiveMailToPlayer(APlayerCharacter* Player)
{
	if (Player->NotesComp)
	{
		for (UNoteData* Note : MailNotes)
		{
			if (Note)
			{
				Player->NotesComp->AddNote(Note);
			}
		}
	}

	MailNotes.Empty(); // Clear the door's mail, but not the player's

	if (APlayerCharacterController* PC = Cast<APlayerCharacterController>(Player->GetController()))
	{
		// Show a "You got new mail" UI notification if you want
	}

	if (InteractionSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractionSound);
	}
}

void AApartmentDoor::TravelToCorridor()
{
	if (LevelTravelName != NAME_None)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelTravelName);
	}
}