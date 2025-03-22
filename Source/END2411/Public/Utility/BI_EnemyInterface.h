// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BI_EnemyInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class END2411_API UBI_EnemyInterface : public UInterface
{
	GENERATED_BODY()
	
}; 


class END2411_API IBI_EnemyInterface 
{
	GENERATED_BODY() 

public:
	// Interface function for attacking
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	void PerformAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	void EnemyReload();
};