// Fill out your copyright notice in the Description page of Project Settings.


#include "OnReloadNow.h"
#include "CharacterAnimation.h"

void UOnReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//Super::Notify(MeshComp, Animation); 
	UCharacterAnimation* AnimationBP = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
	if (AnimationBP) {
		AnimationBP->OnReloadNow.Broadcast();
	}
	
}
