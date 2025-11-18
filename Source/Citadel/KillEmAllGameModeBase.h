// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CitadelGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_API AKillEmAllGameModeBase : public ACitadelGameModeBase
{
	GENERATED_BODY()

public:

	// create a virtual function a for passing the pawn that is killed and overide it
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	//Private function for checking if all enemies killed and the player is winner
	void EndGame(bool bIsPlayerWinner);
};
