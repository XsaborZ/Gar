// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeMenuWidget.generated.h"

UCLASS()
class END2411_API UCodeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;


public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCodeButton* StartGameButton; 
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCodeButton* QuitGameButton; 
	
};
