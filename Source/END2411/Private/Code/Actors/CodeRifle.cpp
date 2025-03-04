// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterAnimation.h"

#include "../END2411.h" // Logger

// Sets default values
ACodeRifle::ACodeRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

#pragma region Day5 Weapon Spawning

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);

#pragma endregion

	Alive = true;

}

// Called when the game starts or when spawned
void ACodeRifle::BeginPlay()
{
	Super::BeginPlay();
	
	ParentPawn = Cast<APawn>(GetParentActor());
	if (!ParentPawn)
	{
		UE_LOG(Game, Error, TEXT("Rifle's parent is not a Pawn"));
		Destroy();
	}

}

// Called every frame
void ACodeRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeRifle::Attack_Implementation()
{
	if (CanShoot() && Alive) {
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
		FRotator BaseAimRotation = ParentPawn->GetBaseAimRotation();
		SpawnParams.Instigator = ParentPawn;
		SpawnParams.Owner = ParentPawn->GetController();

		
	
		GetWorld()->SpawnActor<AActor>(ProjectileClass, GetSource(), BaseAimRotation, SpawnParams);
		
		ActionHapenning = true;
		FTimerHandle ActionTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &ACodeRifle::ActionStopped, 2.0f); // time between shots
		// Broadcast the OnAttack event
		OnAttack.Broadcast(this);
	}
	else {
		//UE_LOG(Game, Warning, TEXT("Can't shoot"));
	}
}

FVector ACodeRifle::GetSource() const
{
	if (SkeletalMesh)
	{
		return SkeletalMesh->GetSocketLocation(FName("MuzzleFlashSocket"));
	}
	return GetActorLocation(); // Fallback to actor location if SkeletalMesh is not valid
}

void ACodeRifle::OwnerDied()
{
	Alive = false;
}

bool ACodeRifle::CanShoot() const
{
	return !ActionHapenning;
}

void ACodeRifle::ActionStopped()
{
	ActionHapenning = false;
}

