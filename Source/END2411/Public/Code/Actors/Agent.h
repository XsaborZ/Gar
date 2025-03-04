// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Agent.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API AAgent : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAgent();
	void Tick(float DeltaTime) override;
	void PostRegisterAllComponents() override;

private:
	void InputAction();
	
};
