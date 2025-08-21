// (C) Anastasis Marinos 2025 //

#include "Player/PlayerGameMode.h"
#include "UObject/ConstructorHelpers.h"

APlayerGameMode::APlayerGameMode()
{
	// Set default pawn class from Blueprint
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Set default player controller class from Blueprint
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/Blueprints/Player/BP_PlayerCharacterController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}