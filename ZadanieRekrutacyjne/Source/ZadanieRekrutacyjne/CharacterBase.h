// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShowTextInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Chest.h"

#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>


#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	void Interact();

protected:
	virtual void BeginPlay() override;

	float InteractionRange = 300.f;

	void ThrowBall();

	bool bIsBallInHand;
	ABall* CollectedBall;

	void AddBall(ABall* Ball);
	void RemoveBall();

	USkeletalMeshComponent* PlayerMesh;
	FName HandSocketName;

	AInteractiveObject* FindInteractiveObject() const;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
