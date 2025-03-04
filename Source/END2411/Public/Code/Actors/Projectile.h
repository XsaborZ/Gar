// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class END2411_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region day 4 Projectile setup

	// Sphere collider component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereCollision;

	// Sphere mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SphereMesh;

	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovement;


#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AController* OwnerController; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Day 4 projectile functions public

	void PostRegisterAllComponents() override;

#pragma endregion

private:
#pragma region Day 4 projectile functions private

	UFUNCTION() // this should not hit
	void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit); 


	UFUNCTION() // this should overlap
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

	void ApplyDamage(AActor* Actor, float DamageAmount, AController* InstigatedBy, AActor* DamageCauser);
};
