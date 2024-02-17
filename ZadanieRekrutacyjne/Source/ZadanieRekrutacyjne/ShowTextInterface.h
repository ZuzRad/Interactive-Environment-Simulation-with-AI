// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShowTextInterface.generated.h"

UINTERFACE(MinimalAPI)
class UShowTextInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZADANIEREKRUTACYJNE_API IShowTextInterface
{
	GENERATED_BODY()

public:
	virtual void SetText(bool isVisible, const FVector& PlayerLocation) = 0;
};
