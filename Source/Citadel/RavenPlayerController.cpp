// Fill out your copyright notice in the Description page of Project Settings.


#include "RavenPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ARavenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Hud = CreateWidget(this, HUDScreenClass);
	if (Hud != nullptr)
	{
		Hud->AddToViewport();
	}

}

void ARavenPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	Hud->RemoveFromViewport();
	if (bIsWinner)
	{
		//create the pointer. check it and then add the widget in the view port
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
		UE_LOG(LogTemp, Warning, TEXT("Player  Wins"));
	}
	else
	{
	//create the pointer. check it and then add the widget in the view port
	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
		UE_LOG(LogTemp, Warning, TEXT("Player Die"));

	}
	
	/// using the  restart level that is ready from the player controller class using a timer to restart the level after 5 sec
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	
}
