
#include "Chest.h"

AChest::AChest()
{
	PrimaryActorTick.bCanEverTick = true;

	Cover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cover"));
	Cover->SetupAttachment(MainPart);

	Hinge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hinge"));
	Hinge->SetupAttachment(MainPart);

	Hole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hole"));
	Hole->SetupAttachment(MainPart);
}


void AChest::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindDynamic(this, &AChest::OpenChest);
		TimeLine.AddInterpFloat(CurveFloat, TimeLineProgress);

		SpawnBallTimerHandle = FTimerHandle();
	}
}

void AChest::OpenChest(float value)
{
	FRotator StartRotation = FRotator(90.f, 0.f, 0.f);
	FRotator EndRotation = FRotator(90.f - CoverRotationAngle, 0.f, 0.f);

	FRotator NewRotation = FMath::Lerp(StartRotation, EndRotation, value);

	Cover->SetRelativeRotation(NewRotation);
}

void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeLine.TickTimeline(DeltaTime);
}

void AChest::OnInteract()
{
	if (bIsChestClosed)
	{
		TimeLine.Play();
		GetWorld()->GetTimerManager().SetTimer(SpawnBallTimerHandle, this, &AChest::SpawnBall, 0.9f, false);
	}
	else
	{
		TimeLine.Reverse();
	}

	bIsChestClosed = !bIsChestClosed;
}

void AChest::SpawnBall()
{
	FTransform SpawnLocation = GetActorTransform();
	SpawnLocation.AddToTranslation(FVector(0.f, 0.f, 1.5f));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABall* SpawnedBall = GetWorld()->SpawnActor<ABall>(BallBP, SpawnLocation, SpawnParameters);

	if (SpawnedBall)
	{
		SpawnedBall->Throw(FVector::BackwardVector);
	}
}

