
#include "CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerMesh = this->GetMesh();
	HandSocketName = FName("hand_r");
}

void ACharacterBase::Interact()
{
	AInteractiveObject* NewObject = FindInteractiveObject();

	if (NewObject)
	{
		ABall* BallObject = dynamic_cast<ABall*>(NewObject);

		if (BallObject && !bIsBallInHand)
		{
			AddBall(BallObject);
			NewObject->OnInteract();
		}
		else if (!BallObject)
		{
			NewObject->OnInteract();
		}
	}
}

AInteractiveObject* ACharacterBase::FindInteractiveObject() const
{
	FHitResult ClosestHitResult;
	float ClosestDistance = InteractionRange;
	AInteractiveObject* ClosestObject = nullptr;

	FVector PlayerLocation = GetActorLocation() - FVector(0, 0, 80);
	FVector PlayerRightVector = GetActorRightVector();

	const int32 NumPoints = 20;

	for (int32 i = 0; i < NumPoints; ++i)
	{
		float Angle = (float)i / (float)NumPoints * 180.0f;
		FRotator Rotation(0.0f, Angle, 0.0f);
		FVector Direction = Rotation.RotateVector(-PlayerRightVector);
		FVector Point = PlayerLocation + Direction * InteractionRange - FVector(0, 0, 20);

		FHitResult HitResult;

		GetWorld()->LineTraceSingleByChannel(HitResult, PlayerLocation, Point, ECollisionChannel::ECC_Visibility);

		DrawDebugLine(GetWorld(), PlayerLocation, HitResult.ImpactPoint, FColor::Green, false, 0.1f, 0, 5);

		AInteractiveObject* Object = Cast<AInteractiveObject>(HitResult.GetActor());
		if (Object)
		{
			float Distance = (HitResult.Location - PlayerLocation).Size();
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestHitResult = HitResult;
				ClosestObject = Object;
			}
		}
	}

	return ClosestObject;
}

void ACharacterBase::ThrowBall()
{
	if (bIsBallInHand)
	{
		bIsThrowing = true;
		CollectedBall->Throw(GetActorForwardVector());
		RemoveBall();
	}
}

void ACharacterBase::AddBall(ABall* Ball)
{
	bIsThrowing = false;
	bIsBallInHand = true;
	CollectedBall = Ball;
}

void ACharacterBase::RemoveBall()
{
	bIsBallInHand = false;
	CollectedBall = nullptr;
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsBallInHand)
	{
		FTransform HandSocketTransform = PlayerMesh->GetSocketTransform(HandSocketName);
		CollectedBall->SetActorLocation(HandSocketTransform.GetLocation() - FVector(0.f, 4.f, 18.f));
		CollectedBall->SetActorRotation(HandSocketTransform.GetRotation());
	}
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

