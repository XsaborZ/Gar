// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API UMyBTTaskNode : public UBTTaskNode // rename class name to FindLocation, keep parent class as UBTTASKNODE  
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; // everything takes place in this funciton.  
	//	Get Owner Controller - OwnerComp
	//  get Controlled Pawn - NodeMemory
	UFUNCTION(BlueprintImplementableEvent, Category = AI)
	void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn); 

	// GetRandomLoctionInNavigableRagius
		// pass in 
		// Get Navigation System - target
		// Get Actor Location - origin
		// Radius - radius value
	// Out Random Loction

	// Set Value as Vector
		// pass in vector Value from randomLocation ^^^
		// Get Blackboard - target
		// Location Name (location) - Key Name
	

	// finish Execute
};
