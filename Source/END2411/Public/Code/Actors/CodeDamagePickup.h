// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/CodePickUp.h"
#include "CodeDamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API ACodeDamagePickup : public ACodePickUp
{
	GENERATED_BODY()

public:
	ACodeDamagePickup();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float damageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool DestroyOnPickup;
	
	UFUNCTION() 
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override; 

	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float BaseDamage, AActor* DamageCauser);
	
	UFUNCTION()
	virtual void PostPickup() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* PickupEffect;

	
};
