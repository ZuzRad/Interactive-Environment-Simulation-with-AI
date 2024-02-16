// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShowTextInterface.h"
#include "Components/TextRenderComponent.h"
#include "InteractiveObject.generated.h"

UCLASS()
class ZADANIEREKRUTACYJNE_API AInteractiveObject : public AActor, public IShowTextInterface
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MainPart;

public:
	AInteractiveObject();

	virtual void Tick(float DeltaTime) override;
	virtual void SetText(bool isVisible, const FVector& PlayerLocation) override;
	virtual void OnInteract();

	UPROPERTY(EditAnywhere, Category = "UI")
	UTextRenderComponent* InteractionText;

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	FVector TextOffset = FVector(0.f, 0.f, 70.f);

};
