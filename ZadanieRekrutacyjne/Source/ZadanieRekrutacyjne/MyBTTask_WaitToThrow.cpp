// MyBTTask_WaitToThrow.cpp
#include "MyBTTask_WaitToThrow.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"

UMyBTTask_WaitToThrow::UMyBTTask_WaitToThrow()
{
    NodeName = TEXT("WaitToThrow");
}

EBTNodeResult::Type UMyBTTask_WaitToThrow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AMainCharacter* MainCharacter = Cast<AMainCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
    if (!MainCharacter)
    {
        return EBTNodeResult::Failed;
    }
    UE_LOG(LogTemp, Warning, TEXT("isThrow? %d"), MainCharacter->bIsThrowing);

    return EBTNodeResult::InProgress;
}

void UMyBTTask_WaitToThrow::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UE_LOG(LogTemp, Warning, TEXT("isThrow!!!!!!!!!?"));
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AMainCharacter* MainCharacter = Cast<AMainCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
    if (!MainCharacter)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (MainCharacter->bIsThrowing)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), MainCharacter->CollectedBall);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }
}

void UMyBTTask_WaitToThrow::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
