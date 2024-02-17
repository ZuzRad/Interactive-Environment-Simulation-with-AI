
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

