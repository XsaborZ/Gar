// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackDelegate, AActor*, Weapon); 

UCLASS()
class END2411_API ACodeRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma region Day 5 Weapon Spawning

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	class APawn* ParentPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float ResetTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	bool Alive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();
	virtual void Attack_Implementation(); // override in c++

	FVector GetSource() const;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnAttackDelegate OnAttack; 
	
	UFUNCTION(BlueprintCallable)
	void OwnerDied();

private:

	UPROPERTY(EditAnywhere, Category = "Default")
	bool ActionHapenning;


	// pure fuction
	UFUNCTION(BlueprintCallable)
	bool CanShoot() const;

	UFUNCTION(BlueprintCallable)
	void ActionStopped();

};
