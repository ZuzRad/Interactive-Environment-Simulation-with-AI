#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ShowTextInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Chest.h"

#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>

#include "MainCharacter.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;

	// Functions to move
	void MoveForward(float value);
	void MoveSideways(float value);


protected:
	virtual void BeginPlay() override;

	// Camera spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraArm;

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;


private:

	// Functions to handle rotation of the character
	void TurnHorizontally(float value);
	void TurnVertically(float value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Rates at which the character rotates
	float TurnRate = 45.f;
	float LookUpRate = 45.f;

	// Function to interact with objects
	void Interact();

	void ShowInteractiveText();

	float InteractionRange = 300.f;


	//TArray<AInteractiveObject*> ObjectsToInteract;
	AInteractiveObject* LastObject;
	AInteractiveObject* FindInteractiveObject() const;

	bool bIsBallInHand;
	ABall* CollectedBall;

	void AddBall(ABall* Ball);
	void RemoveBall();

	USkeletalMeshComponent* PlayerMesh;
	FName HandSocketName;

	void ThrowBall();
	
};
