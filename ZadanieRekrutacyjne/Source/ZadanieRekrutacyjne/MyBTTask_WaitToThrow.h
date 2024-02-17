// MyBTTask_WaitToThrow.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_WaitToThrow.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API UMyBTTask_WaitToThrow : public UBTTask_BlackboardBase
{
    GENERATED_BODY()

public:
    UMyBTTask_WaitToThrow();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

};
