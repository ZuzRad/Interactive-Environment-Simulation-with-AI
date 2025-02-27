// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ThrowBall.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ZADANIEREKRUTACYJNE_API UBTTask_ThrowBall : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ThrowBall();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
