// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class END2411_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
#pragma region Day 3 Native animation

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 

#pragma endregion

protected:

#pragma region Day 3 Idle and Walking

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;

#pragma endregion

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SlotNodeName)
	FName ActionSlotName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Asset)
	class UAnimSequence* FireAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debug);
	bool DebugHit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Asset)
	class UAnimSequence* HitAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Asset)
	class UAnimSequenceBase* CurrentDeathAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Asset)
	TArray<UAnimSequenceBase*> DeathAssets;

	UCharacterAnimation();

	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debug)
	bool DebugFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debug)
	bool DebugDeath;
	

public:

	

	UFUNCTION(BlueprintNativeEvent)
	void FireAnimation();
	virtual void FireAnimation_Implementation();

	UFUNCTION(BlueprintCallable)
	void HitAnimation();
	UFUNCTION(BlueprintCallable)
	void DeathAnimation();

};
