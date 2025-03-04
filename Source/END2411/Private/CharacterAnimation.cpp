// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimation.h"
#include <KismetAnimationLibrary.h>



UCharacterAnimation::UCharacterAnimation()
{
	DebugFire = false;
	DebugHit = false;
	DebugDeath = false;
	ActionSlotName = "Action";
}

#pragma region Day 3 idle walking animation

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn) {
		// is valid
		//FVector Vel = Pawn->GetVelocity();
		Velocity = Pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
	else {
		// Not valid
		PreviewWindowUpdate(); // Added Day 6
	}

}


#pragma endregion


void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	if (DebugFire) {
		DebugFire = false;
		FireAnimation();
	}
	if (DebugHit) {
		DebugHit = false;
		HitAnimation();
	}
	if (DebugHit) {
		DebugDeath = false;
		DeathAnimation();
	}
}

void UCharacterAnimation::FireAnimation_Implementation()
{
	UAnimInstance::PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
}

void UCharacterAnimation::HitAnimation()
{
	UAnimInstance::PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
}

void UCharacterAnimation::DeathAnimation()
{
	int32 RandDeathAsset = FMath::RandRange(0, DeathAssets.Num() - 1);
 	CurrentDeathAsset = DeathAssets[RandDeathAsset];
}
