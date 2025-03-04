// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:

#pragma region Day 1 SpringArm & Camera

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UCameraComponent* Camera;

#pragma endregion

#pragma region Day 3 Movement
	void InputAxisMoveForward(float AxisValue);
	void InputAxisStrafe(float AxisValue);
#pragma endregion

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<class UUserWidget> WidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	class UUserWidget* PlayerHUDWidget; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class APlayerController* PlayerController;

public:
	
	ABasePlayer(); 

#pragma region Day 2 Player Controls

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

	virtual FRotator GetBaseAimRotation() const override;

private:

	void AttackInput();

	class UHealthComponent* HealthComponent;

	virtual void HandleHurt(float Ratio) override;
	virtual void HandleDeadStart(float Ratio) override;
};
