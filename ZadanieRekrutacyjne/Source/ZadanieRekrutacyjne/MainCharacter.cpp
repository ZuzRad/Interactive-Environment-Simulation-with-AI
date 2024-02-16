
#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Disable character rotation in Yaw, Pitch, and Roll by the controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Rotate the character to face the direction of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Set jump settings
	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = 0.3f;


	// Create the SpringArm component for the camera
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);

	// Set camera length and rotation
	CameraArm->TargetArmLength = 350.f;
	CameraArm->bUsePawnControlRotation = true;

	// Create the camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerMesh = this->GetMesh();
	HandSocketName = FName("hand_r");
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShowInteractiveText();
	if (bIsBallInHand)
	{
		FTransform HandSocketTransform = PlayerMesh->GetSocketTransform(HandSocketName);
		CollectedBall->SetActorLocation(HandSocketTransform.GetLocation() - FVector(0.f, 4.f, 18.f));
		CollectedBall->SetActorRotation(HandSocketTransform.GetRotation());
	}
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Assign axes to functions responsible for rotations
	PlayerInputComponent->BindAxis("TurnHorizontally", this, &AMainCharacter::TurnHorizontally);
	PlayerInputComponent->BindAxis("TurnVertically", this, &AMainCharacter::TurnVertically);

	// Assign jump action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	// Assign axes to functions responsible for movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &AMainCharacter::MoveSideways);

	// Assign interaction action
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);

	// Assign throw action
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AMainCharacter::ThrowBall);
}


void AMainCharacter::MoveForward(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		// Get the character's forward direction
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
		// Get the character's sideways direction
		FRotator CharRotation = Controller->GetControlRotation();
		FRotator ZRotation(0.f, CharRotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(ZRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::AddBall(ABall* Ball)
{
	bIsBallInHand = true;
	CollectedBall = Ball;
}

void AMainCharacter::RemoveBall()
{
	bIsBallInHand = false;
	CollectedBall = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("balls %d"), bIsBallInHand);
}

void AMainCharacter::ThrowBall()
{
	if (bIsBallInHand)
	{
		CollectedBall->Throw(GetActorForwardVector());
		RemoveBall();
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