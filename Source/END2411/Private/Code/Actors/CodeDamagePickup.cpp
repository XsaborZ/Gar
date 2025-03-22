// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeDamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"

ACodeDamagePickup::ACodeDamagePickup()
{
	PickupEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PickupEffect"));
	PickupEffect->SetupAttachment(CollisionBox);
	PickupEffect->bAutoActivate = true;
	PickupEffect->SetVisibility(true, true);
}

void ACodeDamagePickup::BeginPlay()
{
	Super::BeginPlay();

	if (PickupEffect)
	{
		PickupEffect->ActivateSystem();
		if (damageAmount == 0) {
			return;
		}
	}
}

void ACodeDamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);

	// apply damage Function
	ApplyDamage(OtherActor, damageAmount, this);
}

void ACodeDamagePickup::ApplyDamage(AActor* DamagedActor, float BaseDamage, AActor* DamageCauser)
{
	if (DamagedActor) {
		TSubclassOf<UDamageType> const ValidDamageTypeClass = UDamageType::StaticClass();
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		DamagedActor->TakeDamage(BaseDamage, DamageEvent, NULL, DamageCauser);
	}
}
