// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Utility/BI_EnemyInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Agent.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API AAgent : public ABaseCharacter, public IBI_EnemyInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AAgent();
	virtual void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void PostRegisterAllComponents() override;

	virtual void PerformAttack_Implementation() override;
	virtual void EnemyReload_Implementation() override; 
	virtual FGenericTeamId GetGenericTeamId() const override;
private:
	void InputAction();

	UFUNCTION()
	void HandleActionFinished(); 

	void UpdateBlackboardHealth(float Ratio);  

	UFUNCTION()
	void UpdateBlackboardAmmo(float Current, float Max);  
	virtual void HandleHurt(float Ratio) override;

};
