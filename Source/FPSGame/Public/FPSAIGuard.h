// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"


class UPawnSensingComponent;
class UWidgetComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicuius,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* WidgetComp;

	UFUNCTION()
		void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
		void ResetOrientation();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChange(EAIState NewState);

	void SetGuardState(EAIState NewState);


	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	//Sync value between client and server
	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
		EAIState GuardState;

	UFUNCTION()
		void OnRep_GuardState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
