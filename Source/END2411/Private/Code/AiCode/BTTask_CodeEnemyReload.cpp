// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/BTTask_CodeEnemyReload.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utility/BI_EnemyInterface.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_CodeEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AActor* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	IBI_EnemyInterface* EnemyInterface = Cast<IBI_EnemyInterface>(ControlledPawn);
	if (EnemyInterface)
	{

	}

	return EBTNodeResult::Failed;
}
