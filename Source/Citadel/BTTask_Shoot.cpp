// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Raven.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	// create a text node name so it will be easier to use it in the BT_Enemy and BB_Enemy
	NodeName = TEXT("Shoot");

}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//hold the ai controller from the behavior tree
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Type();
	}
	
	// setting the pointer casting to raven getting the Aicontroller and the pawn that using it
	ARaven* Character = Cast<ARaven>(OwnerComp.GetAIOwner()->GetPawn()); 
	if (Character == nullptr)
	{
		return EBTNodeResult::Type();
	}
	// after casting and checking use the shoot function from the characcter
	Character->Shoot();

	return EBTNodeResult::Type();
}
