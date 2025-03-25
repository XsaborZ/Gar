// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	
	UFUNCTION(BlueprintCallable, Category = "Game Events")
	void LoadFirstLevel();
	
	UFUNCTION(BlueprintCallable, Category = "Game Events")
	void QuitGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FirstLevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> GameLevels;

	void LoadLevelSafe(int index);
};
