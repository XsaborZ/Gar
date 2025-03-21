// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/BT_CodeAttackPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Utility/BI_EnemyInterface.h"
#include "AIController.h"

EBTNodeResult::Type UBT_CodeAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		EnemyInterface->Execute_PerformAttack(ControlledPawn);
		//OwnerComp.RegisterMessageObserver(this, (FName)"ActionFinished"); 
		WaitForMessage(OwnerComp, (FName)"ActionFinished");
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}