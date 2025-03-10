// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/AIC_CodeAgentController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/NavigationSystemBase.h"
#include "GameFramework/Character.h"

AAIC_CodeAgentController::AAIC_CodeAgentController()
{
}

void AAIC_CodeAgentController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
	
	if (BTAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTAsset is valid. Starting Behavior Tree"));  
        if (RunBehaviorTree(BTAsset)) 
        {
            UE_LOG(LogTemp, Warning, TEXT("Behavior Tree started successfully.")); 
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to start Behavior Tree!")); 
        }
	}
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BTAsset is nullptr during OnPossess!"));
    }
}
