// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/CodeGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UCodeGameInstance::LoadFirstLevel()
{
	LoadLevelSafe(FirstLevelIndex);
}

void UCodeGameInstance::LoadLevelSafe(int index)
{
	//still needs the checker for level
	if (GameLevels.IsValidIndex(index))
	{
		FName LevelName = GameLevels[index];
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LoadLevelSafe: Invalid index %d"), index); 
	}
}



void UCodeGameInstance::QuitGame()
{
	UWorld* World = GetWorld(); 
	APlayerController* PlayerController = World->GetFirstPlayerController(); 
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}

void UCodeGameInstance::LoadCurrentLevel()
{
	LoadLevelSafe(CurrentLevelIndex);
}

void UCodeGameInstance::LoadMainMenu()
{
	LoadLevelSafe(0);
}

