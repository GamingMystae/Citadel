// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CleatBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_API UBTTask_CleatBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	//Create the constractor
	UBTTask_CleatBlackboardValue();

protected:
	// virtual function from the ebt component.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
