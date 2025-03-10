// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AiCode/AIC_CodeAgentController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/NavigationSystemBase.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

AAIC_CodeAgentController::AAIC_CodeAgentController()
{
    UE_LOG(LogTemp, Warning, TEXT("AI Controller Constructor Called!"));
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
    if (AIPerceptionComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIPerceptionComp Successfully Created!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AIPerceptionComp is NULL!"));
    }

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
        UE_LOG(LogTemp, Warning, TEXT("SightConfig Successfully Configured!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SightConfig is NULL!"));
    }

    if (AIPerceptionComp)
    {
        AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::HandlePerception);
        UE_LOG(LogTemp, Warning, TEXT("HandlePerception successfully bound to Perception Component!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AIPerceptionComp is NULL!"));
    }
}
void AAIC_CodeAgentController::BeginPlay()
{
    Super::BeginPlay();

    if (AIPerceptionComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIPerception Component Activated!"));
        AIPerceptionComp->Activate();
    }
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

void AAIC_CodeAgentController::HandlePerception(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor || !GetBlackboardComponent()) {
        return;
    }

    FName PlayerName = (FName)Actor->GetName();

    if (Stimulus.WasSuccessfullySensed())
    {
        GetBlackboardComponent()->SetValueAsObject(PlayerName, Actor);
    }
    else // not successful
    {
        GetBlackboardComponent()->ClearValue(PlayerName);
    }
}