// (C) Anastasis Marinos 2025 //

#include "Actors/FixedCamera.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "CineCameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"

#include "Player/PlayerCharacter.h"

AFixedCamera::AFixedCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CineCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera"));
	CineCamera->SetupAttachment(SceneRoot);

	CameraTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraTrigger"));
	CameraTrigger->SetupAttachment(SceneRoot);
	CameraTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CameraTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	CameraTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CameraTrigger->SetBoxExtent(FVector(200.f));
}

void AFixedCamera::BeginPlay()
{
	Super::BeginPlay();

	CameraTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFixedCamera::OnTriggerBeginOverlap);
	CameraTrigger->OnComponentEndOverlap.AddDynamic(this, &AFixedCamera::OnTriggerEndOverlap);

	// Delay initial overlap check to avoid race conditions at spawn
	GetWorld()->GetTimerManager().SetTimer(OverlapCheckTimerHandle, this,
		&AFixedCamera::CheckInitialOverlap, 0.5f, false);
}

void AFixedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FacePlayer();
}

void AFixedCamera::CheckInitialOverlap()
{
	TArray<AActor*> OverlappingActors;
	CameraTrigger->GetOverlappingActors(OverlappingActors, APlayerCharacter::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(Actor))
		{
			TrackedPlayer = Player;
			SwitchCamera();
			FacePlayer();
			break;
		}
	}
}

void AFixedCamera::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                         bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		TrackedPlayer = Player;
		SwitchCamera();
	}
}

void AFixedCamera::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == TrackedPlayer)
	{
		TrackedPlayer = nullptr;
	}
}

void AFixedCamera::SwitchCamera()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetViewTargetWithBlend(this, CameraBlendTime);
	}
}

void AFixedCamera::FacePlayer()
{
	if (!TrackedPlayer || !CineCamera) return;

	const FVector CameraLocation = CineCamera->GetComponentLocation();
	const FVector PlayerLocation = TrackedPlayer->GetActorLocation();

	FRotator TargetRotation = (PlayerLocation - CameraLocation).Rotation();
	FRotator CurrentRotation = CineCamera->GetComponentRotation();

	TargetRotation.Pitch = CurrentRotation.Pitch;
	TargetRotation.Roll = CurrentRotation.Roll;

	CineCamera->SetWorldRotation(FMath::RInterpTo(CurrentRotation, TargetRotation,
		GetWorld()->GetDeltaSeconds(), InterpSpeed));
}
