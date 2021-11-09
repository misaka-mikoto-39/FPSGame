// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool IsMissionComplete)
{
	if (InstigatorPawn)
	{
		//this is for 1 player game, delete for multiplayer purpose
		//InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewtarget = ReturnedActors[0];
				//multiplayer
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PlayerController = It->Get();
					if (PlayerController)
					{
						PlayerController->SetViewTargetWithBlend(NewViewtarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewPointClass is null"));
		}
	}
	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (GameState)
	{
		GameState->MulticastOnMissionComplete(InstigatorPawn, IsMissionComplete);
	}
	OnMissionComplete(InstigatorPawn, IsMissionComplete);
}
