// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitToThrow.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"
#include "AIControllerBase.h"

UBTTask_WaitToThrow::UBTTask_WaitToThrow()
{
    NodeName = TEXT("WaitToThrow");
}

EBTNodeResult::Type UBTTask_WaitToThrow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AMainCharacter* MainCharacter = Cast<AMainCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
    if (!MainCharacter)
    {
        return EBTNodeResult::Failed;
    }

    if (MainCharacter->CollectedBall)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), MainCharacter->CollectedBall);
    }

    return EBTNodeResult::Succeeded;
}

void UBTTask_WaitToThrow::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
