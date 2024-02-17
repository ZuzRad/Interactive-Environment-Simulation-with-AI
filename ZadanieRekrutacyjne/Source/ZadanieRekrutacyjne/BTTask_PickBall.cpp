// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PickBall.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ball.h"
#include "CharacterBase.h"

UBTTask_PickBall::UBTTask_PickBall()
{
    NodeName = TEXT("PickBall");
}


EBTNodeResult::Type UBTTask_PickBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABall* Ball = Cast<ABall>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
    ACharacterBase* Target = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
    if (!Target->bIsThrowing)
    {
        return EBTNodeResult::Failed;
    }

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
    AIChar->AddBall(Ball);
    Ball->OnInteract();

    return EBTNodeResult::Succeeded;
}

