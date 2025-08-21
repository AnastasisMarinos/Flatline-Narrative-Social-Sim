// (C) Anastasis Marinos 2025 //

#include "Player/Components/PlayerStatsComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerGameInstance.h"

UPlayerStatsComponent::UPlayerStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Default decay values
	StatDecay.Hunger  = -0.15f;
	StatDecay.Thirst  = -0.25f;
	StatDecay.Energy  = -0.15f;
	StatDecay.Hygiene = -0.15f;
	StatDecay.Toilet  =  0.20f;
}

void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceRef = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	LoadStatsFromGameInstance();

	// Start decay loop
	GetWorld()->GetTimerManager().SetTimer(StatDecayTimer, this, &UPlayerStatsComponent::DecayStats, 1.0f, true);
}

void UPlayerStatsComponent::DecayStats()
{
	ChangeStats(StatDecay);
}

void UPlayerStatsComponent::ChangeStats(const FPlayerStatsStruct& StatsChange)
{
	PlayerStats.Hunger  += StatsChange.Hunger;
	PlayerStats.Thirst  += StatsChange.Thirst;
	PlayerStats.Energy  += StatsChange.Energy;
	PlayerStats.Toilet  += StatsChange.Toilet;
	PlayerStats.Hygiene += StatsChange.Hygiene;

	SaveStatsToGameInstance();
}

void UPlayerStatsComponent::SaveStatsToGameInstance()
{
	if (GameInstanceRef)
	{
		GameInstanceRef->PlayerStats = PlayerStats;
		GameInstanceRef->PlayerStats.ClampStats();
	}
}

void UPlayerStatsComponent::LoadStatsFromGameInstance()
{
	if (GameInstanceRef)
	{
		PlayerStats = GameInstanceRef->PlayerStats;
	}
}
