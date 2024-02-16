// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZadanieRekrutacyjneGameMode.h"
#include "ZadanieRekrutacyjneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZadanieRekrutacyjneGameMode::AZadanieRekrutacyjneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
