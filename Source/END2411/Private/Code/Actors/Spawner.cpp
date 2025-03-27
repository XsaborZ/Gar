// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Spawner.h"
#include "Utility/MyActorComponent.h"
#include "Code/Actors/Agent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpawnerMesh");
	//SetRootComponent(SpawnerMesh);
	HealthComponent = CreateDefaultSubobject<UMyActorComponent>("HealthComponent"); 
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHurt.AddDynamic(this, &ASpawner::HandleHurt);
	HealthComponent->OnDead.AddDynamic(this, &ASpawner::OnDead);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Spawning)
	{
		Spawning = true;
		FTimerHandle SpawnTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::SpawnEnemy, 5.0f);
	}
}

void ASpawner::SpawnEnemy() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* newAgent = GetWorld()->SpawnActor<AActor>(Agent, SpawnerMesh->GetRelativeTransform(), SpawnParams); 
	if (newAgent) {
		newAgent->SetActorScale3D(FVector(1.0f));
	}
	OnSpawn.Broadcast(newAgent);
	Spawning = false;
}

void ASpawner::HandleHurt(float HealthPercent)
{
	// flash red on hit

}

void ASpawner::OnDead(float HealthPercent) 
{
	Destroy();
}

