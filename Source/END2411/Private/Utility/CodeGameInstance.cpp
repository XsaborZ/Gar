// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/CodeGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UCodeGameInstance::LoadFirstLevel()
{

}

void UCodeGameInstance::QuitGame()
{
	UWorld* World = GetWorld(); 
	APlayerController* PlayerController = World->GetFirstPlayerController(); 
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}
