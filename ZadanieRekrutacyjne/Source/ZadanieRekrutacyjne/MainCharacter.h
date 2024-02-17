#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"



#include "CharacterBase.h"
#include "MainCharacter.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;

	// Functions to move
	void MoveForward(float value);
	void MoveSideways(float value);

	AInteractiveObject* LastObject;


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

	void ShowInteractiveText();
};
