// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h" 
#include "Code_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API ACode_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf <UUserWidget> MenuClass;

private:
	UPROPERTY()
	UUserWidget* MenuInstance; 
};
