// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SpawnerInterface.h"

// Add default functionality here for any ISpawnerInterface functions that are not pure virtual.

void ISpawnerInterface::EnemySpawned_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interface Spawner called!"));
}
