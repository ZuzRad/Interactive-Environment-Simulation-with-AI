
#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = 0.3f;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 350.f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShowInteractiveText();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnHorizontally", this, &AMainCharacter::TurnHorizontally);
	PlayerInputComponent->BindAxis("TurnVertically", this, &AMainCharacter::TurnVertically);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &AMainCharacter::MoveSideways);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);

	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ACharacterBase::ThrowBall);
}


void AMainCharacter::MoveForward(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		FRotator CharacterRotation = Controller->GetControlRotation();
		FRotator ZRotation(0.f, CharacterRotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(ZRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::MoveSideways(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		FRotator CharRotation = Controller->GetControlRotation();
		FRotator ZRotation(0.f, CharRotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(ZRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::TurnHorizontally(float value)
{
	AddControllerYawInput(value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::TurnVertically(float value)
{
	AddControllerPitchInput(value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::ShowInteractiveText()
{
	AInteractiveObject* NewObject = FindInteractiveObject();
	if (NewObject)
	{
		NewObject->SetText(true, GetActorLocation());
		LastObject = NewObject;
	}
	else if (LastObject)
	{
		LastObject->SetText(false, FVector::ZeroVector);
		LastObject = nullptr;
	}
}

void AMainCharacter::Interact()
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

AInteractiveObject* AMainCharacter::FindInteractiveObject() const
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
