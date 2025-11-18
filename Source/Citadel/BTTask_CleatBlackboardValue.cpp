// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CleatBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

// constractor
UBTTask_CleatBlackboardValue::UBTTask_CleatBlackboardValue()
{
	// create a text node name so it will be easier to use it in the BT_Enemy and BB_Enemy
	NodeName = TEXT("Clear BlackBoard Value");
}

EBTNodeResult::Type UBTTask_CleatBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// getting from the owner the blackboard component
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	
	return EBTNodeResult::Type();
}
