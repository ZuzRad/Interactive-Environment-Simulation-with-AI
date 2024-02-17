// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ZADANIEREKRUTACYJNE_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:

	AAIControllerBase(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	class AMainCharacter* Agent;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BTC;

	UPROPERTY(Transient)
	class UBlackboardComponent* BBC;

	uint8 TargetKeyId;
	uint8 LocationKeyId;
};
