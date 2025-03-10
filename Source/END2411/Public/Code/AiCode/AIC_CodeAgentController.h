// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIC_CodeAgentController.generated.h"



/**
 * 
 */
UCLASS()
class END2411_API AAIC_CodeAgentController : public AAIController
{
	GENERATED_BODY() 

public:
	AAIC_CodeAgentController();

    virtual void BeginPlay() override; 

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
    class UBehaviorTree* BTAsset;

    
protected:
    virtual void OnPossess(APawn* InPawn) override;  

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAISenseConfig_Sight* SightConfig;

private:
    UFUNCTION()
    void HandlePerception(AActor* Actor, FAIStimulus Stimulus);
};
