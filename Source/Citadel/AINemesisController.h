// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AINemesisController.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_API AAINemesisController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	//create a constant bool variab
	bool IsDead() const;

private:
	
	UPROPERTY(EditAnywhere, Category = "Values Settings")
	class UBehaviorTree* AIBehavior;

};
