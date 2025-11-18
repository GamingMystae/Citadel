// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CitadelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_API ACitadelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// create a virtual function a for passing the pawn that is killed
	virtual void PawnKilled(APawn* PawnKilled);
	
};
