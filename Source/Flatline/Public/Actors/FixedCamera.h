// (C) Anastasis Marinos 2025 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FixedCamera.generated.h"

// Forward declarations
class APlayerCharacter;
class UCineCameraComponent;
class UBoxComponent;

/**
 * AFixedCamera
 *
 * An actor with a fixed-position cinematic camera and a trigger volume.
 * When the player enters the trigger, the camera blends into view and
 * rotates to face the player.
 */
UCLASS()
class FLATLINE_API AFixedCamera : public AActor
{
	GENERATED_BODY()

public:
	AFixedCamera();

	/** Root scene component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USceneComponent* SceneRoot;

	/** Cinematic camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCineCameraComponent* CineCamera;

	/** Trigger volume for detecting player overlaps */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UBoxComponent* CameraTrigger;

	/** Time (seconds) to blend camera transition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float CameraBlendTime = 0.5f;

	/** Interpolation speed for camera facing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float InterpSpeed = 2.0f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** Currently tracked player */
	UPROPERTY()
	APlayerCharacter* TrackedPlayer = nullptr;

	/** Delay handle for initial overlap check */
	FTimerHandle OverlapCheckTimerHandle;

	// --- Internal Methods ---

	/** Called after a short delay to detect if player is already inside trigger */
	UFUNCTION()
	void CheckInitialOverlap();

	/** Handles player entering trigger */
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                           bool bFromSweep, const FHitResult& SweepResult);

	/** Handles player leaving trigger */
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Switch player's camera view to this fixed camera */
	void SwitchCamera();

	/** Smoothly rotates camera to face the tracked player */
	void FacePlayer();
};
