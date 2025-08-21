// (C) Anastasis Marinos 2025 //

#include "Actors/Interactables/ConsumableBase.h"

#include "Player/PlayerCharacter.h"
#include "Player/Components/PlayerStatsComponent.h"

AConsumableActor::AConsumableActor()
{
}

void AConsumableActor::Interact_Implementation(APlayerCharacter* Player)
{
	if (!Player) return;

	Super::Interact_Implementation(Player);
	
	if (!(CurrentAmountOfUses >= MaxAmountOfUses && !bCanInteract))
	{
		UPlayerStatsComponent* Stats = Player->GetPlayerStats();
		if (Stats)
		{
			Stats->ChangeStats(PlayerStatsChange);

			if (MaxAmountOfUses > -1)
			{
				CurrentAmountOfUses++;
			}
		}
	}
	else
	{
		bCanInteract = false;
	}
}
