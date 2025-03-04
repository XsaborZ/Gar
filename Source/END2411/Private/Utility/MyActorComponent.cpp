// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MyActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "../END2411.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay(); 
	if (MaxHealth == 0) 
	{
		MaxHealth = 5;
	}
	CurrentHealth = MaxHealth;

	AActor* Owner = GetOwner();

	Owner->OnTakeAnyDamage.AddDynamic(this, &UMyActorComponent::HandleDamage);
	UE_LOG(LogTemp, Warning, TEXT("%s Current health is: %f"), *Owner->GetName(), CurrentHealth);
	
	// ...
	
}


void UMyActorComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	AActor* Owner = GetOwner();
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	float HealthPercent = CurrentHealth / MaxHealth;

	if (CurrentHealth > 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("%s took a hit. Current health is: %f"), *Owner->GetName(), CurrentHealth);

		OnHurt.Broadcast(HealthPercent);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("%s Current health is < 0 : %f"), *Owner->GetName(), CurrentHealth);

		Owner->OnTakeAnyDamage.RemoveDynamic(this, &UMyActorComponent::HandleDamage);
		float dead = 0;
		OnDead.Broadcast(dead); 
	}
	OnTakeAnyDamage.Broadcast(Damage); 
}

// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

