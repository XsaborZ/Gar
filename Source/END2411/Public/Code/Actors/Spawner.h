// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnedDelegate, AActor*, EnemyActor);

UCLASS()
class END2411_API ASpawner : public AActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UMyActorComponent* HealthComponent; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default") 
	TSubclassOf<AActor> Agent; 



private:

	bool Spawning = false;


public:	
	// Sets default values for this actor's properties
	ASpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Default")
	FOnSpawnedDelegate OnSpawn;

	UFUNCTION()
	void HandleHurt(float HealthPercent); 
	UFUNCTION()
	void OnDead(float HealthPercent); 
	UFUNCTION()
	void SpawnEnemy();

};
