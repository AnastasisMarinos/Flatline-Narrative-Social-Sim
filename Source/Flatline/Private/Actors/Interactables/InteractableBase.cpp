#include "Actors/Interactables/InteractableBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterController.h"

AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.f));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnOverlapEnd);
}

void AInteractableBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		Player->SetCurrentInteractable(this);
	}
}

void AInteractableBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		Player->ClearCurrentInteractable(this);
	}
}

void AInteractableBase::Interact_Implementation(APlayerCharacter* Player)
{
	if (!Player) return;
	
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(Player->GetController());
	if (!PlayerController)
		return;

	if (!bCanInteract)
	{
		PlayerController->ShowErrorMessage(InteractionErrorMessage);
		return;
	}

	// Play 2D interaction sound if assigned
	if (InteractionSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractionSound);
	}

	// Notify UI of successful interaction via PlayerController
	PlayerController->BlinkOnInteraction(BlinkTime);
	
	Player->SetCurrentInteractable(this);
}
