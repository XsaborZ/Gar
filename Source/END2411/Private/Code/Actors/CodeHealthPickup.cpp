// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeHealthPickup.h"
#include "Utility/Bi_PickupInterface.h"
#include "END2411/END2411.h"

bool ACodeHealthPickup::CanPickup(AActor* OtherActor)
{
    if (OtherActor->Implements<UBi_PickupInterface>()) 
    {
        UE_LOG(LogTemp, Warning, TEXT("OtherActor class: %s implements Bi_PickupInterface"), *OtherActor->GetClass()->GetName());

        //bool bResult = IBi_PickupInterface::Execute_CanPickUpHealth(OtherActor);

        //UE_LOG(LogTemp, Warning, TEXT("CanPickUpHealth returned: %s"), bResult ? TEXT("true") : TEXT("false"));

        //return bResult;

        // Swapped off Execute cause I spent 20 hours trying to get the overrides working.  it not once stepped into the overrides.  
        // So i have no idea if this is done corectly but it works like the example now

        IBi_PickupInterface* InterfaceInstance = Cast<IBi_PickupInterface>(OtherActor);;
        if (InterfaceInstance) {
            return InterfaceInstance->Execute_CanPickUpHealth(OtherActor);
        }
        return false;
    }
    UE_LOG(LogTemp, Warning, TEXT("%s does NOT implement IBi_PickupInterface"), *OtherActor->GetName());
    return false;
}

