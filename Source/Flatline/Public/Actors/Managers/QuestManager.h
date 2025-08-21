// (C) Anastasis Marinos 2025
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UPlayerGameInstance;
class UQuestData;
class APlayerCharacterController;

UCLASS()
class FLATLINE_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	AQuestManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quests")
	TArray<UQuestData*> AllQuests;

	UFUNCTION(BlueprintCallable)
	void TriggerQuestByID(FName QuestID);

protected:
	virtual void BeginPlay() override;

private:
	void StartQuest(UQuestData* Quest);
	void PlayNextLine();

	UPROPERTY()
	UQuestData* CurrentQuest;

	int32 CurrentLineIndex;

	FTimerHandle LineTimer;

	UPROPERTY()
	APlayerCharacterController* PlayerControllerRef;
	
	UPROPERTY()
	UPlayerGameInstance* GameInstanceRef = nullptr;
};
