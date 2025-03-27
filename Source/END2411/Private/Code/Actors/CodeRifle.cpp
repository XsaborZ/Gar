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

	// call reload to set max ammo
	ReloadAmmo();

}



// Called every frame
void ACodeRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeRifle::Attack_Implementation()
{
	if (CanShoot() && Alive && currentAmmo > 0) {
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
		FRotator BaseAimRotation = ParentPawn->GetBaseAimRotation();
		SpawnParams.Instigator = ParentPawn;
		SpawnParams.Owner = ParentPawn->GetController();
	
		GetWorld()->SpawnActor<AActor>(ProjectileClass, GetSource(), BaseAimRotation, SpawnParams);
		
		ActionHapenning = true;
		FTimerHandle ActionTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &ACodeRifle::ActionStopped, ResetTime); // time between shots
		// Broadcast the OnAttack event
		OnAttack.Broadcast(this);
		UseAmmo();
	}
	else {
		//UE_LOG(Game, Warning, TEXT("Can't shoot"));
		// promt for reload
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

void ACodeRifle::ReloadAmmo()
{
	// Set Current Ammo with Max Ammo
	currentAmmo = maxAmmo; 
	// Call On Ammo Changed
	OnAmmoChanged.Broadcast(currentAmmo,maxAmmo);
	//ActionHapenning = false; // remove this line when reload animation is made
}

void ACodeRifle::UseAmmo()
{
	currentAmmo--;
	currentAmmo = FMath::Max(currentAmmo, 0); // does not go below 0

	OnAmmoChanged.Broadcast(currentAmmo, maxAmmo);
}

void ACodeRifle::MaxAmmo()
{
	//OriginalMaxAmmo = maxAmmo;
	maxAmmo++;
	//ReloadAmmo();
	OnAmmoChanged.Broadcast(currentAmmo, maxAmmo);
	//FTimerHandle MaxAmmoTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(MaxAmmoTimerHandle, this, &ACodeRifle::ResetAmmo, 10, false);
}
void ACodeRifle::ResetAmmo()  // use if ammo needs to be reset to an original value
{
	maxAmmo = OriginalMaxAmmo;
	ReloadAmmo();
	OnAmmoChanged.Broadcast(currentAmmo, maxAmmo);
}
void ACodeRifle::RequestReload()
{
	if (!ActionHapenning) {
		ActionHapenning = true;
		OnRequestReload.Broadcast();
		//ReloadAmmo(); 
	}
}

bool ACodeRifle::CanShoot() const
{
	return !ActionHapenning;
}

void ACodeRifle::ActionStopped()
{
	ActionHapenning = false;
	OnActionStopped.Broadcast();
	//UE_LOG(LogTemp, Warning, TEXT("Brodcasted"));
}

