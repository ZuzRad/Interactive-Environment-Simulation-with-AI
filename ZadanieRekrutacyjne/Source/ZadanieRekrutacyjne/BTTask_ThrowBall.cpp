// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ThrowBall.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "CharacterBase.h"

UBTTask_ThrowBall::UBTTask_ThrowBall()
{
    NodeName = TEXT("ThrowBall");
}

EBTNodeResult::Type UBTTask_ThrowBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIOwner = Cast<AAIController>(OwnerComp.GetAIOwner());
    if (AIOwner == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ACharacterBase* AIChar = Cast<ACharacterBase>(AIOwner->GetPawn());
    if (AIChar == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AIChar->ThrowBall();
    
    AIChar->Destroy();
    return EBTNodeResult::Succeeded;
}
