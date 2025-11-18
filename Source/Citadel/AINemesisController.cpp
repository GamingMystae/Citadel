// Fill out your copyright notice in the Description page of Project Settings.


#include "AINemesisController.h"
#include "Kismet/GameplayStatics.h"
#include "behaviorTree/BlackboardComponent.h"
#include "Raven.h"

void AAINemesisController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (APawn* ControlledPawn = GetPawn())
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), ControlledPawn->GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AAINemesisController: GetPawn() returned nullptr in BeginPlay."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AAINemesisController: AIBehavior is nullptr in BeginPlay."));
	}
}

void AAINemesisController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

bool AAINemesisController::IsDead() const
{

	ARaven* ControlledCharacter = Cast<ARaven>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	
	return true;
}

