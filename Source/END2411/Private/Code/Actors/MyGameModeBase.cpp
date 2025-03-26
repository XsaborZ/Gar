// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MyGameModeBase.h"
#include "Code/Actors/BaseCharacter.h"
#include "Code/Actors/BasePlayer.h"
#include "WBP_CodeResultsWidget.h" 
#include "Blueprint/UserWidget.h"
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
			Player = Cast<ABasePlayer>(Character);
			if (!Player) {
				AddEnemy(Character);
			}
			else {
				Player->OnPlayerLost.AddDynamic(this, &AMyGameModeBase::RemovePlayer);
			}
			
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Number of Enemies: %d"), NumOfEnemies);

	if (ResultsWidgetsClass)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		ResultsWidget = CreateWidget<UWBP_CodeResultsWidget>(PlayerController, ResultsWidgetsClass); 
		if (ResultsWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Widge is Set")); 
		}
	}
}

void AMyGameModeBase::RemovePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("You Lost"));
	ResultsWidget->AddToViewport();
	ResultsWidget->Setlose();
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(ResultsWidget->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	ResultsWidget->GetOwningPlayer()->SetInputMode(InputMode);
}

void AMyGameModeBase::RemoveEnemy(AActor* Actor)
{
	NumOfEnemies--;
	if (!(NumOfEnemies > 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Number of Enemies: %d, You Win"), NumOfEnemies);
		ResultsWidget->AddToViewport();
		ResultsWidget->SetWin();
		Player->PlayerWin();
	}

}

void AMyGameModeBase::AddEnemy(AActor* EnemyActor)
{
	NumOfEnemies++;
	EnemyActor->OnDestroyed.AddDynamic(this, &AMyGameModeBase::RemoveEnemy);
}
