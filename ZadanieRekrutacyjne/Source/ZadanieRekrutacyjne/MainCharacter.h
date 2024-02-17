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

	void MoveForward(float value);
	void MoveSideways(float value);

	AInteractiveObject* LastObject;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

private:

	void TurnHorizontally(float value);
	void TurnVertically(float value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TurnRate = 45.f;
	float LookUpRate = 45.f;

	void ShowInteractiveText();

	void Interact();

	AInteractiveObject* FindInteractiveObject() const;
};
