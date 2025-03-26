#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bi_PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class END2411_API UBi_PickupInterface : public UInterface 
{
	GENERATED_BODY()
};

/**
 *
 */
class END2411_API IBi_PickupInterface
{
	GENERATED_BODY()

public:
	// Declaring the BlueprintNativeEvent
	UFUNCTION(BlueprintNativeEvent)
	bool CanPickUpHealth();
	virtual bool CanPickUpHealth_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void CanPickAmmoBox();
	virtual void CanPickAmmoBox_Implementation();
};
