
#include "Ball.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABall::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Interakcja z pi³k¹!"));
	InteractionText->SetVisibility(false);
	MainPart->SetSimulatePhysics(false);
	MainPart->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
}

