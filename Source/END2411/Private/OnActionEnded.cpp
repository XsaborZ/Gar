// Fill out your copyright notice in the Description page of Project Settings.


#include "OnActionEnded.h"
#include "CharacterAnimation.h"

void UOnActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UCharacterAnimation* AnimationBP = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
	if (AnimationBP) {
		AnimationBP->OnActionEnded.Broadcast();
	}
}
