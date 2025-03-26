// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackDelegate, AActor*, Weapon); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStoppedDelegate); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChangedDelegate, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestReloadDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMaxAmmoDelegate); 

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float maxAmmo;
	UPROPERTY(BlueprintReadOnly)
	float OriginalMaxAmmo;

	UFUNCTION(BlueprintCallable)
	void UseAmmo();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();
	virtual void Attack_Implementation(); // override in c++

	UFUNCTION(BlueprintCallable)
	void MaxAmmo();

	UFUNCTION(BlueprintCallable)
	void ActionStopped();

	FVector GetSource() const;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnAttackDelegate OnAttack; 
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default") 
	FOnActionStoppedDelegate OnActionStopped;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnAmmoChangedDelegate OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")  
	FOnRequestReloadDelegate OnRequestReload;
	
	//UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")  
	//FOnMaxAmmoDelegate OnMaxAmmo;


	UFUNCTION(BlueprintCallable)
	void OwnerDied();
	UFUNCTION(BlueprintCallable)
	void ReloadAmmo();
	UFUNCTION(BlueprintCallable)
	void RequestReload(); 

private:

	float currentAmmo;


	UPROPERTY(EditAnywhere, Category = "Default")
	bool ActionHapenning;


	// pure fuction
	UFUNCTION(BlueprintCallable)
	bool CanShoot() const;

	

};
