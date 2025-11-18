// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RavenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_API ARavenPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// virtual void from player controller
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	// using the float variable for restartung the game after the player dies
	UPROPERTY(EditAnywhere, Category = "Restart Timer");
	float RestartDelay = 5.0f;

	//timer handler
	FTimerHandle RestartTimer;

	//calling the blueprint and we can choose it in the contoller blueprint for lose condition
	UPROPERTY(EditAnywhere);
	TSubclassOf<class UUserWidget> LoseScreenClass;

	//calling the blueprint and we can choose it in the contoller blueprint for win condition
	UPROPERTY(EditAnywhere);
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<class UUserWidget> HUDScreenClass;

	UPROPERTY(EditAnywhere);
	UUserWidget* Hud;
};
