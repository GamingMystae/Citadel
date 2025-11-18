// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h" // helper header
#include "GameFramework/Controller.h"
#include "AINemesisController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("A Pawn Was Killed"));
	
	// casting the player controller so we can see if the pawn that is dead is the player
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		//set the end game false because the player is killed
		EndGame(false);
		// Destroy all AI controllers when the player dies and stope shooting
		for (AAINemesisController* NemesisController : TActorRange<AAINemesisController>(GetWorld()))
		{
			if (NemesisController != nullptr)
			{
				NemesisController->Destroy(); // destroy the AI controller
				UE_LOG(LogTemp, Warning, TEXT("Destroyed AIController: %s"), *NemesisController->GetName());
			}
		}
		return;
	}
	 // for llop over AIcharacter in world
	//if dead or not
	for (AAINemesisController* AIController : TActorRange<AAINemesisController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
		EndGame(true);

	}

}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	//creat a for loop for all the controllers in the world
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// setting the player to player controller and checking with booleans if the player is the only controller in the game
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // following the controller of the allive pawn
		
			
	}
}
