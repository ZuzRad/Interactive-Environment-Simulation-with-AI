
#include "Ball.h"
#include <DrawDebugHelpers.h>

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	Trajectory = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trajectory"));
	Trajectory->SetupAttachment(MainPart);
}

void ABall::OnInteract()
{
	InteractionText->SetVisibility(false);
	MainPart->SetSimulatePhysics(false);
	MainPart->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Trajectory->SetPaused(true);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall::Throw(FVector ImpulseDirection)
{
	MainPart->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainPart->SetSimulatePhysics(true);
	MainPart->AddImpulse(ImpulseDirection * ImpulsePower);

	Trajectory->SetPaused(false);
}
