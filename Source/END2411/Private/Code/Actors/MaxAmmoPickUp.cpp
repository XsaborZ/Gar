// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MaxAmmoPickUp.h"
#include "Components/StaticMeshComponent.h"	
#include "Utility/Bi_PickupInterface.h"

AMaxAmmoPickUp::AMaxAmmoPickUp()
{
	AmmoCrateMesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoCrateMesh");
	AmmoCrateMesh->SetupAttachment(CollisionBox);
	AmmoCrateMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AMaxAmmoPickUp::CanPickup(AActor* OtherActor)
{
	// interface stuff so only player can pickup
	IBi_PickupInterface* InterfaceInstance = Cast<IBi_PickupInterface>(OtherActor);;
	if (InterfaceInstance) {
		return InterfaceInstance->Execute_CanPickUpHealth(OtherActor);
	}
	return false;
}

void AMaxAmmoPickUp::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);
	GrantMaxAmmo(OtherActor);
}

void AMaxAmmoPickUp::GrantMaxAmmo(AActor* Actor)
{
	IBi_PickupInterface* InterfaceInstance = Cast<IBi_PickupInterface>(Actor);;
	if (InterfaceInstance) {
		InterfaceInstance->Execute_CanPickAmmoBox(Actor);
	}
}
