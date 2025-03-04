// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h" // sphere collider
#include "Components/StaticMeshComponent.h"	//sphere mesh
#include "GameFramework/ProjectileMovementComponent.h" // projectile movement
#include "Engine/DamageEvents.h"


#include "..//END2411.h" // Logger

//#include "UObject/ConstructorHelpers.h"  // for bad habbit

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	

#pragma region Day 4 setting up components

	//sphere collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic); 
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);  

	//sphere mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->SetupAttachment(SphereCollision);

	// poor habbit example
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	//SphereMesh->SetStaticMesh(Asset.Object);

	//movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->Activate(true);

#pragma region setting up internal addDynamic functions

	// 1 right-click the delegate and go to declaration
	// 2 Right-click the type and go to delclaration
	// 3 copy from the back how many input params is declared
	// 4 Declare a function that returns void and paste copied inputs
	// 5 Get rid of extra commas
	// 6 Define the function
	// SphereCollision->OnComponentHit.AddDynamic(this, &AProjectile::HandleHit);
	// Note this is the same as adding an event in BP

#pragma endregion

	// setting Projectile Speed
	ProjectileMovement->InitialSpeed = 1900.0f; // setting to 0 to test spawns on attack input
	ProjectileMovement->MaxSpeed = 1900.0f;

#pragma endregion

	Damage = 1.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	

#pragma region Day 4 destroy on overlap or on timer

	//OverLap function calling 
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap);

	// Timed Destruction
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AProjectile::K2_DestroyActor, 3.f);

#pragma endregion

	OwnerController = Cast<AController>(GetOwner());
}

#pragma region basic componets setter

void AProjectile::PostRegisterAllComponents() {
	Super::PostRegisterAllComponents();

	ProjectileMovement->ProjectileGravityScale = 0.0f; // No Gravity set to 0
	//Setting World Scale
	SphereCollision->SetWorldScale3D(FVector{0.18f, 0.18f, 0.18f});
	SphereMesh->SetRelativeScale3D(FVector{ 0.6f,0.6f,0.6f }); // scale of the projectiles
}

#pragma endregion

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Day 4 collider functions

// this will never get hit cause obj is overlap all
void AProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(Game, Log, TEXT("Hello"));  
	Destroy();
}

void AProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (OtherActor)
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = UDamageType::StaticClass();
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		UE_LOG(Game, Log, TEXT("Projectile Overlapped with Actor: %s"), *OtherActor->GetName());
		ApplyDamage(OtherActor, Damage, OwnerController, this);
	}

	// when componet encounters another component
	UE_LOG(Game, Log, TEXT("OverLap took place"));
	Destroy(); 
}

void AProjectile::ApplyDamage(AActor* Actor, float DamageAmount, AController* InstigatedBy, AActor* DamageCauser)
{
	TSubclassOf<UDamageType> const ValidDamageTypeClass = UDamageType::StaticClass();
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	Actor->TakeDamage(DamageAmount, DamageEvent, OwnerController, this);
	Destroy();
}

#pragma endregion
