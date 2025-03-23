// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeHealthPickup.h"
#include "Utility/Bi_PickupInterface.h"
#include "END2411/END2411.h"

bool ACodeHealthPickup::CanPickup(AActor* OtherActor)
{
    if (OtherActor->Implements<UBi_PickupInterface>()) 
    {
        UE_LOG(LogTemp, Warning, TEXT("%s execute_canpickuphealth"), *OtherActor->GetName());
        return IBi_PickupInterface::Execute_CanPickUpHealth(OtherActor);
    }
    UE_LOG(LogTemp, Warning, TEXT("%s does NOT implement IBi_PickupInterface"), *OtherActor->GetName()); 
    return false;
}

