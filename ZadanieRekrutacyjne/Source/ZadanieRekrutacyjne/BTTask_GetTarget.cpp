// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetTarget.h"

UBTTask_GetTarget::UBTTask_GetTarget()
{
	NodeName = TEXT("GetTarget");
}

EBTNodeResult::Type UBTTask_GetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCharacter::StaticClass(), FoundActors);

    AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    FVector AIPosition = AIController->GetPawn()->GetActorLocation();

    AActor* ClosestActor = FindClosestActor(FoundActors, AIPosition);

    if (!ClosestActor)
    {
        return EBTNodeResult::Failed;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), ClosestActor);

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}

AActor* UBTTask_GetTarget::FindClosestActor(const TArray<AActor*>& Actors, const FVector& ReferencePosition)
{
    AActor* ClosestActor = nullptr;
    float ClosestDistanceSquared = MAX_FLT;

    for (AActor* Actor : Actors)
    {
        if (Actor)
        {
            float DistanceSquared = FVector::DistSquared(Actor->GetActorLocation(), ReferencePosition);
            if (DistanceSquared < ClosestDistanceSquared)
            {
                ClosestActor = Actor;
                ClosestDistanceSquared = DistanceSquared;
            }
        }
    }

    return ClosestActor;
}



