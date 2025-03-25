// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Code_GamePlayerController.h"

void ACode_GamePlayerController::BeginPlay()
{
    Super::BeginPlay();


    PrimaryActorTick.bStartWithTickEnabled = true; 
    PrimaryActorTick.bCanEverTick = true; 

    FInputModeGameOnly InputMode; 
    SetInputMode(InputMode);  
    bShowMouseCursor = false; 

    // Optionally, log the current input mode or other debug information
    UE_LOG(LogTemp, Log, TEXT("ACode_GamePlayerController: Input Mode set to GameOnly, Mouse Cursor Hidden")); 
}

