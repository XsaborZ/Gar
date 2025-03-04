// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeAnyDamage, float, Other);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurt, float, HealthPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, float, Ratio);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class END2411_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY() 

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	//Create a variable of the Delegate type created above line 12
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnTakeAnyDamage OnTakeAnyDamage;

	//Create a variable of the Delegate type created above line 12
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnHurt OnHurt;

	//Create a variable of the Delegate type created above line 12
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnDead OnDead;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MaxHealth;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float CurrentHealth;

	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


};
