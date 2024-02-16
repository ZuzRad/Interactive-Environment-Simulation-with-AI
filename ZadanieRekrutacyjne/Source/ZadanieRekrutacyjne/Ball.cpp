
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

bool ABall::IsInCollision()
{
	FVector StartLocation = MainPart->GetComponentLocation(); // Pobierz pozycjê pi³ki
	FVector EndLocation = StartLocation - FVector(0.f, 0.f, 100.f); // Przesuniêcie o wartoœæ TraceDistance (100.f w przyk³adzie)
	FHitResult HitResult;

	// Ustawienia trace
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, this);
	TraceParams.bTraceComplex = true;

	// Wykonanie trace
	bool bHit = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParams
	);

	DrawDebugLine(
		GetWorld(),
		StartLocation,
		HitResult.ImpactPoint,
		FColor::Red,
		false,
		2.f,
		0,
		1.f
	);

	return bHit;
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Trajectory->SetPaused(IsInCollision());
}

void ABall::Throw(FVector ImpulseDirection)
{
	MainPart->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainPart->SetSimulatePhysics(true);

	MainPart->AddImpulse(ImpulseDirection * ImpulsePower);
	Trajectory->SetPaused(false);
}
//
//TArray<AActor*> OverlappingActors;
//MainPart->GetOverlappingActors(OverlappingActors);
//
//UE_LOG(LogTemp, Warning, TEXT("Actors %d"), OverlappingActors.Num());
//
//return OverlappingActors.Num() == 0;