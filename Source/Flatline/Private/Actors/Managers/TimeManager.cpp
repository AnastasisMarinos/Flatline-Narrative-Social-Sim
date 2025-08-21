// (C) Anastasis Marinos 2025 //

#include "Actors/Managers/TimeManager.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerGameInstance.h"
#include "Math/UnrealMathUtility.h"

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

	MinutesSinceLastRainCheck = 0;
	bIsRaining = false;

	// Create AudioComponent
	RainAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RainAudioComponent"));
	RainAudioComponent->SetupAttachment(RootComponent);
	RainAudioComponent->bAutoActivate = false;
}

void ATimeManager::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceRef = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	LoadTimeFromGameInstance();

	// Start timer to call AdvanceTime every RealSecondsPerMinute seconds
	GetWorldTimerManager().SetTimer(AdvanceTimerHandle, this, &ATimeManager::AdvanceTime, RealSecondsPerMinute, true);

	// Broadcast initial values once so UI / listeners can initialize
	OnTimeChanged.Broadcast(TimeStruct);
	OnWeatherChanged.Broadcast(bIsRaining);
}

void ATimeManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SaveTimeToGameInstance();
	
	GetWorldTimerManager().ClearTimer(AdvanceTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void ATimeManager::AdvanceTime()
{
	// Increase time
	TimeStruct.Minute += MinuteIncrement;

	// Handle minute->hour rollover
	if (TimeStruct.Minute >= 60)
	{
		int32 ExtraHours = TimeStruct.Minute / 60;
		TimeStruct.Minute = TimeStruct.Minute % 60;
		TimeStruct.Hour += ExtraHours;
	}

	// Handle hour->day rollover
	if (TimeStruct.Hour >= 24)
	{
		int32 ExtraDays = TimeStruct.Hour / 24;
		TimeStruct.Hour = TimeStruct.Hour % 24;
		TimeStruct.Day += ExtraDays;

		// Very basic month rollover (no calendar complexity)
		if (TimeStruct.Day > 31)
		{
			TimeStruct.Day = 1;
			TimeStruct.Month++;
			if (TimeStruct.Month > 12)
			{
				TimeStruct.Month = 1;
			}
		}
	}

	// Broadcast time tick
	OnTimeChanged.Broadcast(TimeStruct);

	// Weather check tracking
	MinutesSinceLastRainCheck += MinuteIncrement;
	if (MinutesSinceLastRainCheck >= RainCheckInterval)
	{
		MinutesSinceLastRainCheck = 0;
		PossiblyToggleRain();
	}
}

void ATimeManager::AdvanceDay()
{
	TimeStruct.Hour = 10;
	TimeStruct.Minute = 0;
	TimeStruct.Day += 1;
	
	// Broadcast new time
	OnTimeChanged.Broadcast(TimeStruct);
}

void ATimeManager::PossiblyToggleRain()
{
	// Simple random check
	const float R = FMath::FRand(); // 0..1
	const bool bShouldRain = (R < RainChance);

	// Only broadcast if state changed
	if (bShouldRain != bIsRaining)
	{
		bIsRaining = bShouldRain;
		OnWeatherChanged.Broadcast(bIsRaining);

		UpdateRainAudio();
	}
}

FString ATimeManager::GetTimeString() const
{
	// Format with leading zeros (HH:MM)
	const FString HourStr = FString::Printf(TEXT("%02d"), FMath::Clamp(TimeStruct.Hour, 0, 23));
	const FString MinuteStr = FString::Printf(TEXT("%02d"), FMath::Clamp(TimeStruct.Minute, 0, 59));
	return HourStr + TEXT(" : ") + MinuteStr;
}

FString ATimeManager::GetDateString() const
{
	return FString::Printf(TEXT("%d / %d"), TimeStruct.Day, TimeStruct.Month);
}

void ATimeManager::SetRaining(bool bNewRaining)
{
	if (bIsRaining != bNewRaining)
	{
		bIsRaining = bNewRaining;
		OnWeatherChanged.Broadcast(bIsRaining);

		UpdateRainAudio();
	}
}

void ATimeManager::UpdateRainAudio()
{
	if (bIsRaining)
	{
		if (RainSoundCue && !RainAudioComponent->IsPlaying())
		{
			RainAudioComponent->SetSound(RainSoundCue);
			RainAudioComponent->Play();
		}
	}
	else
	{
		if (RainAudioComponent->IsPlaying())
		{
			RainAudioComponent->Stop();
		}
	}
}

void ATimeManager::SaveTimeToGameInstance()
{
	if (GameInstanceRef)
	{
		GameInstanceRef->TimeStruct = TimeStruct;
	}
}

void ATimeManager::LoadTimeFromGameInstance()
{
	if (GameInstanceRef)
	{
		TimeStruct = GameInstanceRef->TimeStruct;
	}
}
