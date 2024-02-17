#include "BTTask_MoveToActor.h"
#include "AIControllerBase.h"



//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "BTTask_MoveToActor.h"
//
//UBTTask_MoveToActor::UBTTask_MoveToActor()
//{
//}
//
//EBTNodeResult::Type UBTTask_MoveToActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//    Super::ExecuteTask(OwnerComp, NodeMemory);
//
//    // Pobierz kontroler AI i czarn¹ tablicê
//    AAIController* AIController = OwnerComp.GetAIOwner();
//    if (!AIController)
//    {
//        return;
//    }
//
//    // Pobierz wartoœæ z czarnej tablicy (np. po³o¿enie docelowego aktora)
//    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
//
//    if (TargetActor)
//    {
//        // Przemieszczaj AI do okreœlonego aktora
//        AIController->MoveToActor(TargetActor, AcceptanceRadius);
//        // Mo¿esz ustawiæ promieñ akceptacji (Acceptance Radius) w Twoim zadaniu,
//        // aby okreœliæ jak blisko AI musi byæ aktor, aby uznaæ, ¿e dotar³o do celu.
//        // Domyœlnie jest to wartoœæ 10.0f.
//
//        // Ustaw status zadania jako "wykonywane"
//        return EBTNodeResult::InProgress;
//    }
//    else
//    {
//        // Jeœli nie uda³o siê pobraæ aktora docelowego z czarnej tablicy,
//        // ustaw status zadania jako "niepowodzenie"
//        return EBTNodeResult::Failed;
//    }
//}

UBTTask_MoveToActor::UBTTask_MoveToActor()
{
	NodeName = TEXT("MoveToActor");
}

EBTNodeResult::Type UBTTask_MoveToActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Wywo³anie ExecuteTask z klasy bazowej dla ewentualnych operacji, które trzeba wykonaæ przed rozpoczêciem zadania.
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Pobranie wskaŸnika na AIControllera, który aktualnie wykonuje to zadanie.
    AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
    if (AIController == nullptr)
    {
        // Jeœli AIController nie jest dostêpny, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Pobranie wskaŸnika na pionek kontrolowany przez AI.
    APawn* AIPawn = AIController->GetPawn();
    if (AIPawn == nullptr)
    {
        // Jeœli pionek AI nie istnieje, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Pobranie nazwy klucza czarnej deski, który zawiera cel, do którego AI powinien siê przemieœciæ.
    FName TargetActorKeyName = GetSelectedBlackboardKey();

    // Pobranie wskaŸnika na aktora (cel) z czarnej deski.
    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKeyName));

    if (TargetActor == nullptr)
    {
        // Jeœli cel nie zosta³ znaleziony, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Wywo³anie funkcji MoveToActor na AIControllerze, aby AI przemieœci³o siê do celu.
    AIController->MoveToActor(TargetActor);

    // Zwrócenie InProgress, poniewa¿ zadanie jest w trakcie wykonywania.
    return EBTNodeResult::InProgress;
}

