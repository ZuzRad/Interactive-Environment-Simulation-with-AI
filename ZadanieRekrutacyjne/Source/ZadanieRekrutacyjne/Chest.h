// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractiveObject.h"
#include "Ball.h"
#include "Chest.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API AChest : public AInteractiveObject
{
	GENERATED_BODY()
	
public:

	AChest();

	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SpawnBall();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABall> BallBP;

protected:

	virtual void BeginPlay() override;

	FTimeline TimeLine;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	bool bIsChestClosed = true;

	UPROPERTY(EditAnywhere)
	float CoverRotationAngle = 50.f;

	UFUNCTION()
	void OpenChest(float value);

private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Cover;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Hinge;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Hole;

	FTimerHandle SpawnBallTimerHandle;

};
