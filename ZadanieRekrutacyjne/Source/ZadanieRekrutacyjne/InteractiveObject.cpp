
#include "InteractiveObject.h"

AInteractiveObject::AInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;

	MainPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainPart"));
	MainPart->SetupAttachment(RootComponent);

	InteractionText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InteractionText"));
	InteractionText->SetupAttachment(MainPart);
}


void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveObject::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("The function should be overwritten"));
}

void AInteractiveObject::SetText(bool isVisible, const FVector& PlayerLocation)
{
	FVector DirectionToPlayer = PlayerLocation - GetActorLocation();
	DirectionToPlayer.Normalize();

	FRotator NewRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
	InteractionText->SetWorldRotation(NewRotation);

	FVector NewLocation = GetActorLocation() + TextOffset;
	InteractionText->SetWorldLocation(NewLocation);


	InteractionText->SetVisibility(isVisible);
}

void AInteractiveObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

