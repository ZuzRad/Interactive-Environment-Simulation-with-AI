// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (!Agent) 
	{
		AMainCharacter* character = Cast<AMainCharacter>(GetPawn());
		if (!character) 
		{
			return;
		}
		Agent = character;
	}
}

AAIControllerBase::AAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTree"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMainCharacter* character = Cast< AMainCharacter>(InPawn);
	if (character && character->AITree) 
	{
		BBC->InitializeBlackboard(*character->AITree->BlackboardAsset);

		TargetKeyId = BBC->GetKeyID("TargetActor");
		TargetKeyId = BBC->GetKeyID("MoveToLocation");

		BTC->StartTree(*character->AITree);
	}
}
