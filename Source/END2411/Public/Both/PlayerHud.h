// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Default")
	FVector GetDestinationCode() const;

	UFUNCTION(BlueprintCallable, Category = "Default")
	FVector GetDestination() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float Percent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Crosshair;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	FName ColorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	FLinearColor SafeColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	FLinearColor DangerColor;

private:
	UPROPERTY(VisibleAnywhere, Category = "Variables|ReadOnly")
	FVector EndPointCode;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Default")
	void SetHealth(float newPercentHealth);
	void SetHealth_Implementation(float newPercentHealth);
};
