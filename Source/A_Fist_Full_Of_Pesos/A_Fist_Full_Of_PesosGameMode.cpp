// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_Fist_Full_Of_PesosGameMode.h"
#include "A_Fist_Full_Of_PesosCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA_Fist_Full_Of_PesosGameMode::AA_Fist_Full_Of_PesosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
