// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.h"
#include "Ball.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API ABall : public AInteractiveObject
{
	GENERATED_BODY()
	
public:
	ABall();
	virtual void OnInteract() override;

	virtual void Tick(float DeltaTime) override;
	void Throw(FVector ImpulseDirection);

protected:
	virtual void BeginPlay() override;

private:
	float ImpulsePower = 8000.f;

};
