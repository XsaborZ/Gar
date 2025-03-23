// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodePickUp.h"

// Sets default values
ACodePickUp::ACodePickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName(TEXT("Collider"));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACodePickUp::OnOverlapBegin); 
}

// Called when the game starts or when spawned
void ACodePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACodePickUp::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{ 
	
}

void ACodePickUp::PostPickup()
{
	Destroy();
}

bool ACodePickUp::CanPickup(AActor* OtherActor)
{
	return true;
}


void ACodePickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool result = CanPickup(OtherActor);
	if (result) {
		HandlePickup(OtherActor, SweepResult);
		PostPickup();
	}
}

// Called every frame
void ACodePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

