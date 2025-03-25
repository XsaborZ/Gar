// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MyGameModeBase.h"
#include "Code/Actors/BaseCharacter.h"
#include "Code/Actors/BasePlayer.h"
#include "EngineUtils.h"
#include "../END2411.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ABaseCharacter> It(GetWorld()); It; ++It) { 
		ABaseCharacter* Character = *It;
		if (Character)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found BaseCharacter: %s"), *Character->GetName());
			ABasePlayer* Player = Cast<ABasePlayer>(Character);
			if (!Player) {
				AddEnemy(Character);
			}
			else {
				Player->OnPlayerLost.AddDynamic(this, &AMyGameModeBase::RemovePlayer);
			}
			
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Number of Enemies: %d"), NumOfEnemies);

	// win loss stuff here
}

void AMyGameModeBase::RemovePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("You Lost"));
}

void AMyGameModeBase::RemoveEnemy(AActor* Actor)
{
	NumOfEnemies--;
	if (!(NumOfEnemies > 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Number of Enemies: %d, You Win"), NumOfEnemies);
	}

}

void AMyGameModeBase::AddEnemy(AActor* EnemyActor)
{
	NumOfEnemies++;
	EnemyActor->OnDestroyed.AddDynamic(this, &AMyGameModeBase::RemoveEnemy);
}
