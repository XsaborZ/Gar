// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Bi_PickupInterface.h"
#include "END2411/END2411.h"

// Add default functionality here for any IBi_PickupInterface functions that are not pure virtual.

bool IBi_PickupInterface::CanPickUpHealth_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Interface called!"));
    return true;
}

void IBi_PickupInterface::CanPickAmmoBox_Implementation() 
{
    UE_LOG(LogTemp, Warning, TEXT("Interface maxAmmo called!"));
}
