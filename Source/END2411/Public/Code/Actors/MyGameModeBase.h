// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int NumOfEnemies = 0;
	
	//UPROPERTY()
	//class WBP_CodeResultsWidget &ResultsWidget;

	UFUNCTION()
	void RemovePlayer();

public:
	UFUNCTION()
	void RemoveEnemy(AActor* Actor);

	UFUNCTION()
	void AddEnemy(AActor* EnemyActor); 

};
