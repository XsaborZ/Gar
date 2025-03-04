// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract) 
class END2411_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UChildActorComponent* ChildActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Default")
	class ACodeRifle* Rifle;

	/*UPROPERTY(BlueprintReadOnly, Category = "Default")
	class UAnimInstance* AnimationClass;*/
	UPROPERTY(BlueprintReadOnly, Category = "Default")
	class UCharacterAnimation* AnimationBP; // change back to UCharacterAnimInstance

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UMyActorComponent* HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void HandleHurt(float HealthPercent);
	UFUNCTION()
	virtual void HandleDeadStart(float Ratio);

private:

	UFUNCTION()
	void OnRifleAttack(AActor* Actor);
};
