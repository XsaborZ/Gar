// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeButton.generated.h"

// delegate onclicked
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedDelegate);

UCLASS()
class END2411_API UCodeButton : public UUserWidget
{
	GENERATED_BODY()
	
private:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override; 

	

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnClickedDelegate OnClickedDelegate; 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Information;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Background_Button;

	void HandleOnClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Info;
};
