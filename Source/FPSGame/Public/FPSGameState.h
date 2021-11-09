// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	//Multicast function, call in all client and server
	UFUNCTION(NetMulticast, Reliable)
		void MulticastOnMissionComplete(APawn* InstigatorPawn, bool IsMissionComplete);
	void MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool IsMissionComplete);
};
