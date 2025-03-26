// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/CodePickUp.h"
#include "MaxAmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API AMaxAmmoPickUp : public ACodePickUp
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* AmmoCrateMesh;

private:
	UFUNCTION()
	void GrantMaxAmmo(AActor* Actor);

public:
	AMaxAmmoPickUp();
	UFUNCTION()
	virtual bool CanPickup(AActor* OtherActor) override;
	UFUNCTION()
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
};
