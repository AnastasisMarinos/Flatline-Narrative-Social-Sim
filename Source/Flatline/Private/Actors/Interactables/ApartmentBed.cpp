#include "Actors/Interactables/ApartmentBed.h"

#include "Player/PlayerCharacter.h"
#include "Player/PlayerGameInstance.h"
#include "Actors/Managers/TimeManager.h"
#include "Kismet/GameplayStatics.h"

AApartmentBed::AApartmentBed()
{
	// Beds usually don't have limited uses unless you want them to
	MaxAmountOfUses = -1; // Infinite

	PlayerStatsChange.Energy = 100.f;
	PlayerStatsChange.Hunger = -50.f;
	PlayerStatsChange.Thirst = -50.f;
	PlayerStatsChange.Toilet = 70.f;
	PlayerStatsChange.Hygiene = -30.f;
}

void AApartmentBed::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimeManager::StaticClass(), FoundManagers);

	if (FoundManagers.Num() > 0)
	{
		TimeManagerRef = Cast<ATimeManager>(FoundManagers[0]);
	}

	GameInstanceRef = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AApartmentBed::Interact_Implementation(APlayerCharacter* Player)
{
	if (!Player) return;

	Super::Interact_Implementation(Player);

	// Advance the in-game day
	if (TimeManagerRef)
	{
		TimeManagerRef->AdvanceDay();
	}

	GameInstanceRef->SaveGameData();
}
