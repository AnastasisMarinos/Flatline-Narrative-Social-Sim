// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/Structs/TimeStruct.h"
#include "TimeManager.generated.h"

class UPlayerGameInstance;
// Time changed (Hour, Minute, Day, Month)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChangedSignature, FTimeStruct, Time);

// Weather changed (bIsRaining)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeatherChangedSignature, bool, bIsRaining);

UCLASS()
class FLATLINE_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimeManager();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FTimerHandle AdvanceTimerHandle;

	// Helper internal counter for rain checks (in in-game minutes)
	int32 MinutesSinceLastRainCheck;

	// Advance the clock (called by timer)
	void AdvanceTime();

	// Helper to run the random rain check
	void PossiblyToggleRain();

public:
	/** Broadcast each time the minute changes */
	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnTimeChangedSignature OnTimeChanged;

	/** Broadcast when weather (rain) toggles */
	UPROPERTY(BlueprintAssignable, Category = "Weather")
	FOnWeatherChangedSignature OnWeatherChanged;

	/** --- Core time state --- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	FTimeStruct TimeStruct;

	/** How many in-game minutes to add each tick (usually 1) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta=(ClampMin="1"))
	int32 MinuteIncrement = 1;

	/** How many real seconds correspond to one in-game minute (e.g. 1.0f => 1 real second = 1 in-game minute) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta=(ClampMin="0.01"))
	float RealSecondsPerMinute = 0.6f;

	/** --- Weather --- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather", meta=(ClampMin="0.0", ClampMax="1.0"))
	float RainChance = 0.20f; // 20% when check occurs

	/** How many in-game minutes between rain checks (e.g. 120 = every two in-game hours) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather", meta=(ClampMin="1"))
	int32 RainCheckInterval = 120;

	/** Is it currently raining? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather")
	bool bIsRaining = false;

	/** Public getter helpers */
	UFUNCTION(BlueprintCallable, Category = "Time")
	FString GetTimeString() const;

	UFUNCTION(BlueprintCallable, Category = "Time")
	FString GetDateString() const;

	/** Forcefully set rain on/off (broadcasts OnWeatherChanged) */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void SetRaining(bool bNewRaining);

	/** Force-add minutes (useful for debugging/test) */
	UFUNCTION(BlueprintCallable, Category = "Time")
	void AdvanceDay();

protected:
	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* RainSoundCue;

	UPROPERTY(VisibleAnywhere, Category="Audio")
	UAudioComponent* RainAudioComponent;

	// Function to update rain audio based on bIsRaining
	void UpdateRainAudio();

	// Save stats to GameInstance (if needed)
	void SaveTimeToGameInstance();

	// Load stats from GameInstance (if needed)
	void LoadTimeFromGameInstance();

private:
	UPROPERTY()
	UPlayerGameInstance* GameInstanceRef = nullptr;
};
