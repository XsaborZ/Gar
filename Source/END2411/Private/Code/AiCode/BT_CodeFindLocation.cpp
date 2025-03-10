// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/BT_CodeFindLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBT_CodeFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }
    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSystem)
    {
        return EBTNodeResult::Failed;
    }

    FVector Origin = ControlledPawn->GetActorLocation();
    FVector RandomLocation;
    FNavLocation NavLocation;

    if (NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, NavLocation))
    {
        RandomLocation = NavLocation.Location;
    }
    else
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsVector("Location", RandomLocation);
    }

    return EBTNodeResult::Succeeded;
}

