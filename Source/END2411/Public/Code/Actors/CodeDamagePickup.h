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
	
	UFUNCTION() 
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override; 

	UFUNCTION()
	virtual void ApplyDamage(AActor* DamagedActor, float BaseDamage, AActor* DamageCauser);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* PickupEffect;

	
};
