// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_CodeResultsWidget.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API UWBP_CodeResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override; 
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCodeButton* RestartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCodeButton* MenuButton;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game Instance")
	class UCodeGameInstance* GameInstance; 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ButtonArea; 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* ResultsSwitch;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TimeToMenu;

	UFUNCTION()
	void SetWin();
	UFUNCTION()
	void Setlose();

private:
	UFUNCTION()
	void LoadMainMenu();
	
};
