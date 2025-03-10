// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/AIC_CodeAgentController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/NavigationSystemBase.h"
#include "GameFramework/Character.h"

AAIC_CodeAgentController::AAIC_CodeAgentController()
{
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    if (SightConfig)
    {
        // Sight Parameters
        SightConfig->SightRadius = 900.0f;           
        SightConfig->LoseSightRadius = 1100.0f;       
        SightConfig->PeripheralVisionAngleDegrees = 40.0f; 

        // Detection
        SightConfig->DetectionByAffiliation.bDetectEnemies = false;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

        AIPerceptionComp->ConfigureSense(*SightConfig);
        AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
    }
    AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::OnTargetPerceptionUpdated); 
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

void AAIC_CodeAgentController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Actor)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Perceived: %s"), *Actor->GetName());

        if (Stimulus.WasSuccessfullySensed())
        {
            UE_LOG(LogTemp, Warning, TEXT("AI sees the target!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("AI lost sight of the target!"));
        }
    }
}