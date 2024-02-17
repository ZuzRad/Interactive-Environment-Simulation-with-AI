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
//    // Pobierz kontroler AI i czarn� tablic�
//    AAIController* AIController = OwnerComp.GetAIOwner();
//    if (!AIController)
//    {
//        return;
//    }
//
//    // Pobierz warto�� z czarnej tablicy (np. po�o�enie docelowego aktora)
//    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
//
//    if (TargetActor)
//    {
//        // Przemieszczaj AI do okre�lonego aktora
//        AIController->MoveToActor(TargetActor, AcceptanceRadius);
//        // Mo�esz ustawi� promie� akceptacji (Acceptance Radius) w Twoim zadaniu,
//        // aby okre�li� jak blisko AI musi by� aktor, aby uzna�, �e dotar�o do celu.
//        // Domy�lnie jest to warto�� 10.0f.
//
//        // Ustaw status zadania jako "wykonywane"
//        return EBTNodeResult::InProgress;
//    }
//    else
//    {
//        // Je�li nie uda�o si� pobra� aktora docelowego z czarnej tablicy,
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
    // Wywo�anie ExecuteTask z klasy bazowej dla ewentualnych operacji, kt�re trzeba wykona� przed rozpocz�ciem zadania.
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Pobranie wska�nika na AIControllera, kt�ry aktualnie wykonuje to zadanie.
    AAIControllerBase* AIController = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
    if (AIController == nullptr)
    {
        // Je�li AIController nie jest dost�pny, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Pobranie wska�nika na pionek kontrolowany przez AI.
    APawn* AIPawn = AIController->GetPawn();
    if (AIPawn == nullptr)
    {
        // Je�li pionek AI nie istnieje, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Pobranie nazwy klucza czarnej deski, kt�ry zawiera cel, do kt�rego AI powinien si� przemie�ci�.
    FName TargetActorKeyName = GetSelectedBlackboardKey();

    // Pobranie wska�nika na aktora (cel) z czarnej deski.
    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKeyName));

    if (TargetActor == nullptr)
    {
        // Je�li cel nie zosta� znaleziony, zwracamy Failed.
        return EBTNodeResult::Failed;
    }

    // Wywo�anie funkcji MoveToActor na AIControllerze, aby AI przemie�ci�o si� do celu.
    AIController->MoveToActor(TargetActor);

    // Zwr�cenie InProgress, poniewa� zadanie jest w trakcie wykonywania.
    return EBTNodeResult::InProgress;
}

