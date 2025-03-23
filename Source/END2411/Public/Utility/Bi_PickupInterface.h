// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bi_PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UBi_PickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2411_API IBi_PickupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanPickUpHealth();
};
