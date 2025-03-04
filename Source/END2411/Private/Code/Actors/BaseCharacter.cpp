// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Code/Actors/CodeRifle.h"
#include "CharacterAnimation.h"
//#include "Code/Actors/CodeRifle.h" 
#include "Utility/MyActorComponent.h"

#include "../END2411.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

#pragma region day 1 mesh rotation and location

	// setting up location and rotation of the mesh set in BP_CodeBasePlayer
	GetMesh()->SetRelativeRotation(FRotator(0., -90.0, 0.));
	GetMesh()->SetRelativeLocation(FVector(0., 0.0, -90.));

#pragma endregion
#pragma region Day 5 Weapon Spawning

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	ChildActorComponent->SetupAttachment(GetMesh(), "PlaceWeaponHere");
	//WeaponClass = AActor::StaticClass(); 

#pragma endregion

	HealthComponent = CreateDefaultSubobject<UMyActorComponent>("HealthComponent");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
#pragma region Day 5 Weapon Spawning

	//ChildActorComponent->SetChildActorClass(WeaponClass);
	Rifle = Cast<ACodeRifle>(ChildActorComponent->GetChildActor());
	
	if (!Rifle)
	{
		UE_LOG(Game, Error, TEXT("Failed to spawn weapon"));
		Rifle->Destroy();
	}

#pragma endregion
	// cast the animInstance class first -> pass down info to characteranimation class for funciton use
	AnimationBP = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance()); // if crash then recast animinstantce separatly again
	if (!AnimationBP)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterAnimInstance is null"));
		Destroy();
	}
	
	Rifle->OnAttack.AddDynamic(this, &ABaseCharacter::OnRifleAttack);
	HealthComponent->OnHurt.AddDynamic(this, &ABaseCharacter::HandleHurt);
	HealthComponent->OnDead.AddDynamic(this, &ABaseCharacter::HandleDeadStart);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ABaseCharacter::HandleHurt(float HealthPercent)
{
	AnimationBP->HitAnimation();
}

void ABaseCharacter::HandleDeadStart(float Ratio)
{
	AnimationBP->DeathAnimation(); 
	SetActorEnableCollision(false);
	Rifle->OwnerDied();
}


void ABaseCharacter::OnRifleAttack(AActor* Actor)
{
	AnimationBP->FireAnimation();
}

