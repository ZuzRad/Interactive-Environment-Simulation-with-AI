// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "AICharacter.h"

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

void AAIControllerBase::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter* character = Cast< AAICharacter>(InPawn);
	if (character && character->AITree) 
	{
		BBC->InitializeBlackboard(*character->AITree->BlackboardAsset);

		TargetKeyId = BBC->GetKeyID("TargetActor");
		LocationKeyId = BBC->GetKeyID("MoveToLocation");
		BallKeyId = BBC->GetKeyID("BallActor");

		BTC->StartTree(*character->AITree);
	}
}
