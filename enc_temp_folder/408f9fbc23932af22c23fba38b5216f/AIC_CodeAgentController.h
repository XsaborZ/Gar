// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
    class UBehaviorTree* BTAsset;

protected:
    virtual void OnPossess(APawn* InPawn) override;    
};
