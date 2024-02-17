// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetTarget.h"

UBTTask_GetTarget::UBTTask_GetTarget()
{
	NodeName = TEXT("GetTarget");
}

EBTNodeResult::Type UBTTask_GetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Pobierz wszystkich graczy typu MainCharacter w grze
    TArray<AActor*> FoundPlayers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundPlayers);

    // Pobierz pozycjê AI
    AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    FVector AIPosition = AIController->GetPawn()->GetActorLocation();

    // ZnajdŸ najbli¿szego gracza
    AActor* ClosestPlayer = FindClosestActor(FoundPlayers, AIPosition);

    if (!ClosestPlayer)
    {
        return EBTNodeResult::Failed;
    }

    // Zapisz najbli¿szego gracza w czarnej desce
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), ClosestPlayer);

    return EBTNodeResult::Succeeded;
}

AActor* UBTTask_GetTarget::FindClosestActor(const TArray<AActor*>& Actors, const FVector& ReferencePosition)
{
    AActor* ClosestActor = nullptr;
    float ClosestDistanceSquared = MAX_FLT;
    AActor* SecondClosestActor = nullptr;
    float SecondClosestDistanceSquared = MAX_FLT;

    for (AActor* Actor : Actors)
    {
        if (Actor)
        {
            float DistanceSquared = FVector::DistSquared(Actor->GetActorLocation(), ReferencePosition);
            if (DistanceSquared < ClosestDistanceSquared)
            {
                SecondClosestActor = ClosestActor;
                SecondClosestDistanceSquared = ClosestDistanceSquared;
                ClosestActor = Actor;
                ClosestDistanceSquared = DistanceSquared;
            }
            else if (DistanceSquared < SecondClosestDistanceSquared)
            {
                SecondClosestActor = Actor;
                SecondClosestDistanceSquared = DistanceSquared;
            }
        }
    }

    if (ClosestActor == SecondClosestActor)
    {
        // Jeœli najbli¿szy aktor to ten sam aktor, zwróæ drugi najbli¿szy
        return SecondClosestActor;
    }
    else
    {
        // W przeciwnym razie zwróæ najbli¿szy aktor
        return ClosestActor;
    }
}



